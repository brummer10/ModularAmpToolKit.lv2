
#include <atomic>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include "lv2/lv2plug.in/ns/ext/state/state.h"
#include "lv2/lv2plug.in/ns/ext/presets/presets.h"
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>

///////////////////////// MACRO SUPPORT ////////////////////////////////

#define PLUGIN_URI "urn:brummer:PowerAmpImpulses"

using std::min;
using std::max;

typedef int PortIndex;

#include "resampler.cc"
#include "resampler-table.cc"
#include "zita-resampler/resampler.h"
#include "gx_resampler.cc"
#include "zita-convolver.cc"
#include "zita-convolver.h"
#include "gx_convolver.cc"
#include "gx_convolver.h"
#include "amp_table.h"
#include "gain.cc"
#include "tone.cc"

////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace powerampimpulses {

class Xpowerampimpulses
{
private:
    int32_t rt_prio;
    int32_t rt_policy;
    float* input0;
    float* output0;
    float* bypass;
    float bypass_;
    float* tube_style;
    float tube_style_;
    float* buffer;
    uint32_t bufsize;
    uint32_t cur_bufsize;
    uint32_t s_rate;
    // bypass ramping
    bool needs_ramp_down;
    bool needs_ramp_up;
    float ramp_down;
    float ramp_up;
    float ramp_up_step;
    float ramp_down_step;
    bool bypassed;
    bool doit;
    bool selection_changed;
    std::atomic<bool> _execute;
    gx_resample::BufferResampler resamp;
    GxSimpleConvolver preampconv;
    gain::Dsp* plugin1;
    tone::Dsp* plugin2;

    // LV2 stuff
    LV2_URID_Map* map;
    LV2_Worker_Schedule* schedule;

    // private functions
    inline float* adjust(float *buf, int32_t size, int set);
    inline bool IsPowerOfTwo(uint32_t x) {return (x >= 64) && ((x & (x - 1)) == 0);}
    inline void run_dsp_(uint32_t n_samples);
    inline void connect_(uint32_t port,void* data);
    inline void init_dsp_(uint32_t rate, uint32_t bufsize);
    inline void connect_all__ports(uint32_t port, void* data);
    inline void activate_f();
    inline void do_work_mono();
    inline void clean_up();
    inline void deactivate_f();
public:
    // LV2 Descriptor
    static const LV2_Descriptor descriptor;
    static const void* extension_data(const char* uri);
    // static wrapper to private functions
    static void deactivate(LV2_Handle instance);
    static void cleanup(LV2_Handle instance);
    static void run(LV2_Handle instance, uint32_t n_samples);
    static void activate(LV2_Handle instance);
    static void connect_port(LV2_Handle instance, uint32_t port, void* data);
    static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
  
    static LV2_Worker_Status work(LV2_Handle                 instance,
                                LV2_Worker_Respond_Function respond,
                                LV2_Worker_Respond_Handle   handle,
                                uint32_t size, const void*    data);
  
    static LV2_Worker_Status work_response(LV2_Handle  instance,
                                         uint32_t    size,
                                         const void* data);
    Xpowerampimpulses();
    ~Xpowerampimpulses();
};

// constructor
Xpowerampimpulses::Xpowerampimpulses() :

    rt_prio(0),
    rt_policy(0),
    input0(NULL),
    output0(NULL),
    bypass(NULL),
    bypass_(2),
    tube_style(NULL),
    tube_style_(0),
    buffer(NULL),
    bufsize(0),
    cur_bufsize(0),
    needs_ramp_down(false),
    needs_ramp_up(false),
    bypassed(false),
    selection_changed(false),
    preampconv(GxSimpleConvolver(resamp)),
    plugin1(gain::plugin()),
    plugin2(tone::plugin())
 {};

// destructor
Xpowerampimpulses::~Xpowerampimpulses() {
    preampconv.stop_process();
    preampconv.cleanup();
    plugin1->del_instance(plugin1);
    plugin2->del_instance(plugin2);
    delete [] buffer;
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Xpowerampimpulses::init_dsp_(uint32_t rate, uint32_t bufsize_)
{
    plugin1->init(rate);
    plugin2->init(rate);
    s_rate = rate;
    if (!rt_policy) rt_policy = SCHED_FIFO;
    // set values for internal ramping
    ramp_down_step = 32 * (256 * rate) / 48000; 
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
    bufsize = bufsize_;
    if (bufsize ) {
        AmpDesc& pre = *getAmpEntry(static_cast<uint32_t>(tube_style_)).data;
        preampconv.pre_count = pre.ir_count;
        preampconv.pre_sr = pre.ir_sr;
        preampconv.pre_data = adjust(pre.ir_data, pre.ir_count, static_cast<int>(tube_style_));
        preampconv.set_samplerate(rate);
        preampconv.set_buffersize(bufsize);
        preampconv.configure(preampconv.pre_count, preampconv.pre_data, preampconv.pre_sr);
        while (!preampconv.checkstate());
        if(!preampconv.start(rt_prio, rt_policy))
            printf("preamp impulse convolver disabled\n");
        else
            _execute.store(false, std::memory_order_release);
    }
}

// connect the Ports used by the plug-in class
void Xpowerampimpulses::connect_(uint32_t port,void* data)
{
    switch ((PortIndex)port)
    {
        case 0:
            input0 = static_cast<float*>(data);
            break;
        case 1:
            output0 = static_cast<float*>(data);
            break;
        case 2:
            bypass = static_cast<float*>(data);
            break;
        case 5:
            tube_style = static_cast<float*>(data);
            break;
        default:
            break;
    }
}

void Xpowerampimpulses::activate_f()
{
    // allocate the internal DSP mem
}

void Xpowerampimpulses::clean_up()
{
    // delete the internal DSP mem
}

void Xpowerampimpulses::deactivate_f()
{
    // delete the internal DSP mem
}

float* Xpowerampimpulses::adjust(float *buf, int32_t size, int set) {
    delete [] buffer;
    buffer = NULL;
    buffer = new float[size];
    float adj = 1.5f;
    float imax = 0.0f;
    for (int i = 0; i<size;++i) {
        imax = max(imax,std::fabs(buf[i]));
    }
    for (int i = 0; i<size;++i) {
        buffer[i] = buf[i] * (adj - imax);
    }
    return buffer;
}

void Xpowerampimpulses::do_work_mono()
{
    if (preampconv.is_runnable()) {
        preampconv.set_not_runnable();
        preampconv.stop_process();
    }
    bufsize = cur_bufsize;

    preampconv.cleanup();
    AmpDesc& pre = *getAmpEntry(static_cast<uint32_t>(tube_style_)).data;
    preampconv.pre_count = pre.ir_count;
    preampconv.pre_sr = pre.ir_sr;
    preampconv.pre_data = adjust(pre.ir_data, pre.ir_count, static_cast<int>(tube_style_));
    preampconv.set_samplerate(s_rate);
    preampconv.set_buffersize(bufsize);
    preampconv.configure(preampconv.pre_count, preampconv.pre_data, preampconv.pre_sr);
    while (!preampconv.checkstate());
    if(!preampconv.start(rt_prio, rt_policy)) {
        printf("preamp impulse convolver update fail\n");
    } else {
        _execute.store(false, std::memory_order_release);
        needs_ramp_up = true;
    }
}

void Xpowerampimpulses::run_dsp_(uint32_t n_samples)
{
    if(n_samples<1) return;
    cur_bufsize = n_samples;
    if (!_execute.load(std::memory_order_acquire) &&
      ((cur_bufsize != bufsize) || tube_style_ != static_cast<uint32_t>(*(tube_style)))) {
        if (!bypassed) {
            needs_ramp_down = true;
            if (cur_bufsize != bufsize) {
                bufsize = cur_bufsize;
                _execute.store(true, std::memory_order_release);
            }
            tube_style_ = static_cast<uint32_t>(*(tube_style));
            selection_changed = true;
        }
    }

    // do inplace processing on default
    if(output0 != input0)
        memcpy(output0, input0, n_samples*sizeof(float));

    float buf0[n_samples];
    // check if bypass is pressed
    if (bypass_ != static_cast<uint32_t>(*(bypass))) {
        bypass_ = static_cast<uint32_t>(*(bypass));
        if (!bypass_) {
            needs_ramp_down = true;
            needs_ramp_up = false;
        } else {
            needs_ramp_down = false;
            needs_ramp_up = true;
            bypassed = false;
        }
    }

    if (needs_ramp_down || needs_ramp_up) {
         memcpy(buf0, input0, n_samples*sizeof(float));
    }
    if (!bypassed) {
        plugin1->compute(n_samples, output0, output0);
        if (!_execute.load(std::memory_order_acquire))
            preampconv.compute(n_samples, output0);
        plugin2->compute(n_samples, output0, output0);
    }

    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down; 
            }
            fade = max(0.0f,ramp_down) /ramp_down_step ;
            output0[i] = output0[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_down <= 0.0) {
            if (selection_changed) {
                selection_changed = false;
                _execute.store(true, std::memory_order_release);
                schedule->schedule_work(schedule->handle,  sizeof(bool), &doit);
            }
            // when ramped down, clear buffer from dsp
            needs_ramp_down = false;
            bypassed = true;
            plugin1->clear_state_f();
            plugin2->clear_state_f();
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
        } else {
            ramp_up = ramp_down;
        }
    } else if (needs_ramp_up) {
        bypassed = false;
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_up < ramp_up_step) {
                ++ramp_up ;
            }
            fade = min(ramp_up_step,ramp_up) /ramp_up_step ;
            output0[i] = output0[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_up >= ramp_up_step) {
            needs_ramp_up = false;
            ramp_up = 0.0;
            ramp_down = ramp_down_step;
        } else {
            ramp_down = ramp_up;
        }
    }
}

void Xpowerampimpulses::connect_all__ports(uint32_t port, void* data)
{
    // connect the Ports used by the plug-in class
    connect_(port,data);
    plugin1->connect(port,data);
    plugin2->connect(port,data);
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Xpowerampimpulses::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
    // init the plug-in class
    Xpowerampimpulses *self = new Xpowerampimpulses();
    if (!self) {
        return NULL;
    }

    const LV2_Options_Option* options  = NULL;
    uint32_t bufsize = 0;
    //printf(" %s\n",descriptor->URI);

    for (int32_t i = 0; features[i]; ++i) {
        if (!strcmp(features[i]->URI, LV2_URID__map)) {
            self->map = (LV2_URID_Map*)features[i]->data;
        }
        else if (!strcmp(features[i]->URI, LV2_WORKER__schedule)) {
            self->schedule = (LV2_Worker_Schedule*)features[i]->data;
        }
        else if (!strcmp(features[i]->URI, LV2_OPTIONS__options)) {
            options = (const LV2_Options_Option*)features[i]->data;
        }
    }
    if (!self->schedule) {
        fprintf(stderr, "Missing feature work:schedule.\n");
        self->_execute.store(true, std::memory_order_release);
    }
    if (!self->map) {
        fprintf(stderr, "Missing feature uri:map.\n");
    }
    else if (!options) {
        fprintf(stderr, "Missing feature options.\n");
    }
    else {
        LV2_URID bufsz_max = self->map->map(self->map->handle, LV2_BUF_SIZE__maxBlockLength);
        LV2_URID bufsz_    = self->map->map(self->map->handle,"http://lv2plug.in/ns/ext/buf-size#nominalBlockLength");
        LV2_URID atom_Int = self->map->map(self->map->handle, LV2_ATOM__Int);
        LV2_URID tshed_pol = self->map->map (self->map->handle, "http://ardour.org/lv2/threads/#schedPolicy");
        LV2_URID tshed_pri = self->map->map (self->map->handle, "http://ardour.org/lv2/threads/#schedPriority");

        for (const LV2_Options_Option* o = options; o->key; ++o) {
            if (o->context == LV2_OPTIONS_INSTANCE &&
              o->key == bufsz_ && o->type == atom_Int) {
                bufsize = *(const int32_t*)o->value;
            }
            if (o->context == LV2_OPTIONS_INSTANCE &&
              o->key == bufsz_max && o->type == atom_Int) {
                if (!bufsize)
                    bufsize = *(const int32_t*)o->value;
            }
            if (o->context == LV2_OPTIONS_INSTANCE &&
                o->key == tshed_pol && o->type == atom_Int) {
                self->rt_policy = *(const int32_t*)o->value;
            }
            if (o->context == LV2_OPTIONS_INSTANCE &&
                o->key == tshed_pri && o->type == atom_Int) {
                self->rt_prio = *(const int32_t*)o->value;
            }
        }

        if (bufsize == 0) {
            fprintf(stderr, "No maximum buffer size given.\n");
        } else {
            printf("using block size: %d\n", bufsize);
        }
    }
    self->init_dsp_((uint32_t)rate, bufsize);
    return (LV2_Handle)self;
}

void Xpowerampimpulses::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
    // connect all ports
    static_cast<Xpowerampimpulses*>(instance)->connect_all__ports(port, data);
}

void Xpowerampimpulses::activate(LV2_Handle instance)
{
    // allocate needed mem
    static_cast<Xpowerampimpulses*>(instance)->activate_f();
}

void Xpowerampimpulses::run(LV2_Handle instance, uint32_t n_samples)
{
    // run dsp
    static_cast<Xpowerampimpulses*>(instance)->run_dsp_(n_samples);
}

void Xpowerampimpulses::deactivate(LV2_Handle instance)
{
    // free allocated mem
    static_cast<Xpowerampimpulses*>(instance)->deactivate_f();
}

void Xpowerampimpulses::cleanup(LV2_Handle instance)
{
    // well, clean up after us
    Xpowerampimpulses* self = static_cast<Xpowerampimpulses*>(instance);
    self->clean_up();
    delete self;
}

LV2_Worker_Status Xpowerampimpulses::work(LV2_Handle instance,
     LV2_Worker_Respond_Function respond,
     LV2_Worker_Respond_Handle   handle,
     uint32_t                    size,
     const void*                 data)
{
  static_cast<Xpowerampimpulses*>(instance)->do_work_mono();
  return LV2_WORKER_SUCCESS;
}

LV2_Worker_Status Xpowerampimpulses::work_response(LV2_Handle instance,
              uint32_t    size,
              const void* data)
{
  //printf("worker respose.\n");
  return LV2_WORKER_SUCCESS;
}

const void* Xpowerampimpulses::extension_data(const char* uri)
{
  static const LV2_Worker_Interface worker = { work, work_response, NULL };
  if (!strcmp(uri, LV2_WORKER__interface))
    {
      return &worker;
    }
  return NULL;
}

const LV2_Descriptor Xpowerampimpulses::descriptor =
{
    PLUGIN_URI ,
    Xpowerampimpulses::instantiate,
    Xpowerampimpulses::connect_port,
    Xpowerampimpulses::activate,
    Xpowerampimpulses::run,
    Xpowerampimpulses::deactivate,
    Xpowerampimpulses::cleanup,
    Xpowerampimpulses::extension_data
};

} // end namespace powerampimpulses

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index)
    {
        case 0:
            return &powerampimpulses::Xpowerampimpulses::descriptor;
        default:
            return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
