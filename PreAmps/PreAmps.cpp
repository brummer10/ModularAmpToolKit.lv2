
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
///////////////////////// MACRO SUPPORT ////////////////////////////////

#define PLUGIN_URI "urn:brummer:PreAmps"

using std::min;
using std::max;

#define always_inline inline __attribute__((__always_inline__))

typedef enum
{
   input0,
   output0,
   bypass,
   GAIN, // , 0.0, -2e+01, 2e+01, 0.1 
   VOLUME, // , 0.0, -2e+01, 2e+01, 0.1 
   AMPSELECT,
} PortIndex;

#define __rt_data __attribute__((section(".rt.data")))
#include "t12ax7.cc"
#include "t12au7.cc"
#include "t12at7.cc"
#include "t6DJ8.cc"
#include "fizz_remover.cc"

////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace preamps {

class Xpreamps
{
private:
    float* input0;
    float* output0;
    float* bypass;
    float bypass_;
    float* ampselect;
    float ampselect_;
    int ampset;
    // bypass ramping
    bool needs_ramp_down;
    bool needs_ramp_up;
    float ramp_down;
    float ramp_up;
    float ramp_up_step;
    float ramp_down_step;
    bool bypassed;

    t12ax7::Dsp* plugin1;
    t12au7::Dsp* plugin2;
    t12at7::Dsp* plugin3;
    t6dj8::Dsp* plugin4;
    fizz_remover::Dsp* plugin5;

    // private functions
    inline void run_dsp_(uint32_t n_samples);
    inline void connect_(uint32_t port,void* data);
    inline void init_dsp_(uint32_t rate);
    inline void connect_all__ports(uint32_t port, void* data);
    inline void activate_f();
    inline void clean_up();
    inline void deactivate_f();
public:
    // LV2 Descriptor
    static const LV2_Descriptor descriptor;
    // static wrapper to private functions
    static void deactivate(LV2_Handle instance);
    static void cleanup(LV2_Handle instance);
    static void run(LV2_Handle instance, uint32_t n_samples);
    static void activate(LV2_Handle instance);
    static void connect_port(LV2_Handle instance, uint32_t port, void* data);
    static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
    Xpreamps();
    ~Xpreamps();
};

// constructor
Xpreamps::Xpreamps() :

    input0(NULL),
    output0(NULL),
    bypass(NULL),
    bypass_(2),
    ampselect(NULL),
    ampselect_(0),
    ampset(0),
    needs_ramp_down(false),
    needs_ramp_up(false),
    bypassed(false),
    plugin1(t12ax7::plugin()),
    plugin2(t12au7::plugin()),
    plugin3(t12at7::plugin()),
    plugin4(t6dj8::plugin()),
    plugin5(fizz_remover::plugin())
     {};

// destructor
Xpreamps::~Xpreamps() {
    plugin1->del_instance(plugin1);
    plugin2->del_instance(plugin2);
    plugin3->del_instance(plugin3);
    plugin4->del_instance(plugin4);
    plugin5->del_instance(plugin5);
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Xpreamps::init_dsp_(uint32_t rate)
{
    plugin1->init(rate);
    plugin2->init(rate);
    plugin3->init(rate);
    plugin4->init(rate);
    plugin5->init(rate);
    // set values for internal ramping
    ramp_down_step = 32 * (256 * rate) / 48000; 
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
}

// connect the Ports used by the plug-in class
void Xpreamps::connect_(uint32_t port,void* data)
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
            ampselect = static_cast<float*>(data);
            break;
        default:
            break;
    }
}

void Xpreamps::activate_f()
{
    // allocate the internal DSP mem
}

void Xpreamps::clean_up()
{
    // delete the internal DSP mem
}

void Xpreamps::deactivate_f()
{
    // delete the internal DSP mem
}

void Xpreamps::run_dsp_(uint32_t n_samples)
{
    if(n_samples<1) return;


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
    // check if selection have changed
    if (ampselect_ != static_cast<uint32_t>(*(ampselect))) {
        if (!bypassed) {
            ampselect_ = static_cast<uint32_t>(*(ampselect));
            needs_ramp_down = true;
            needs_ramp_up = true;
        }
    } 

    if (needs_ramp_down || needs_ramp_up) {
         memcpy(buf0, input0, n_samples*sizeof(float));
    }
    if (!bypassed) {
        switch (ampset) {
            case 0:
                plugin1->compute(n_samples, output0, output0);
            break;
            case 1:
                plugin2->compute(n_samples, output0, output0);
            break;
            case 2:
                plugin3->compute(n_samples, output0, output0);
            break;
            case 3:
                plugin4->compute(n_samples, output0, output0);
            break;
            default:
            break;
        }
        plugin5->compute(n_samples, output0, output0);
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
            // when ramped down, clear buffer from dsp
            plugin1->clear_state_f();
            plugin2->clear_state_f();
            plugin3->clear_state_f();
            plugin4->clear_state_f();
            plugin5->clear_state_f();
            needs_ramp_down = false;
            bypassed = true;
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
            ampset = static_cast<int>(ampselect_);
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

void Xpreamps::connect_all__ports(uint32_t port, void* data)
{
    // connect the Ports used by the plug-in class
    connect_(port,data); 
    plugin1->connect(port,data);
    plugin2->connect(port,data);
    plugin3->connect(port,data);
    plugin4->connect(port,data);
    plugin5->connect(port,data);
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Xpreamps::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
    // init the plug-in class
    Xpreamps *self = new Xpreamps();
    if (!self) {
        return NULL;
    }
    self->init_dsp_((uint32_t)rate);
    return (LV2_Handle)self;
}

void Xpreamps::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
    // connect all ports
    static_cast<Xpreamps*>(instance)->connect_all__ports(port, data);
}

void Xpreamps::activate(LV2_Handle instance)
{
    // allocate needed mem
    static_cast<Xpreamps*>(instance)->activate_f();
}

void Xpreamps::run(LV2_Handle instance, uint32_t n_samples)
{
    // run dsp
    static_cast<Xpreamps*>(instance)->run_dsp_(n_samples);
}

void Xpreamps::deactivate(LV2_Handle instance)
{
    // free allocated mem
    static_cast<Xpreamps*>(instance)->deactivate_f();
}

void Xpreamps::cleanup(LV2_Handle instance)
{
    // well, clean up after us
    Xpreamps* self = static_cast<Xpreamps*>(instance);
    self->clean_up();
    delete self;
}

const LV2_Descriptor Xpreamps::descriptor =
{
    PLUGIN_URI ,
    Xpreamps::instantiate,
    Xpreamps::connect_port,
    Xpreamps::activate,
    Xpreamps::run,
    Xpreamps::deactivate,
    Xpreamps::cleanup,
    NULL
};

} // end namespace preamps

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index)
    {
        case 0:
            return &preamps::Xpreamps::descriptor;
        default:
            return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
