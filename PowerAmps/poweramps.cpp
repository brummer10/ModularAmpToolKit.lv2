
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
///////////////////////// MACRO SUPPORT ////////////////////////////////

#define PLUGIN_URI "urn:brummer:poweramps"

template<class T> inline T mydsp_faustpower2_f(T x) {return (x * x);}
template<class T> inline T mydsp_faustpower3_f(T x) {return ((x * x) * x);}
template<class T> inline T mydsp_faustpower4_f(T x) {return (((x * x) * x) * x);}
template<class T> inline T mydsp_faustpower5_f(T x) {return ((((x * x) * x) * x) * x);}
template<class T> inline T mydsp_faustpower6_f(T x) {return (((((x * x) * x) * x) * x) * x);}

#define always_inline inline __attribute__((__always_inline__))
#define __rt_func //__attribute__((section("TEXT,.rt.text")))
#define __rt_data //__attribute__((section("DATA,.rt.data")))

typedef enum
{
   input0,
   output0,
   bypass,
   GAIN, // , 0.0, -3e+01, 3e+01, 0.1 
   VOLUME, // , 0.0, -3e+01, 3e+01, 0.1 
   SelectModel,
} PortIndex;

using std::min;
using std::max;

#include "champ.cc"
#include "epiphone.cc"
#include "orangedarkterror.cc"
#include "plexiel34.cc"
#include "princetone.cc"
#include "supersonic.cc"
#include "fizz_remover.cc"

////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace poweramps {

class Xpoweramps
{
private:
    float* input0;
    float* output0;
    float* bypass;
    float bypass_;
    float* sel;
    float sel_;
    champ::Dsp* plugin0;
    epiphone::Dsp* plugin1;
    orangedarkterror::Dsp* plugin2;
    plexiel34::Dsp* plugin3;
    princeton::Dsp* plugin4;
    supersonic::Dsp* plugin5;
    fizz_remover::Dsp* plugin6;
    // ramp down/up when selected model change
    bool needs_ramp_down;
    bool needs_ramp_up;
    float ramp_down;
    float ramp_up;
    float ramp_up_step;
    float ramp_down_step;
    bool bypassed;

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
    Xpoweramps();
    ~Xpoweramps();
};

// constructor
Xpoweramps::Xpoweramps() :

    input0(NULL),
    output0(NULL),
    bypass(NULL),
    bypass_(2),
    plugin0(champ::plugin()),
    plugin1(epiphone::plugin()),
    plugin2(orangedarkterror::plugin()),
    plugin3(plexiel34::plugin()),
    plugin4(princeton::plugin()),
    plugin5(supersonic::plugin()),
    plugin6(fizz_remover::plugin()),
    needs_ramp_down(false),
    needs_ramp_up(false),
    bypassed(false)
{};

// destructor
Xpoweramps::~Xpoweramps() {
    plugin0->del_instance(plugin0);
    plugin1->del_instance(plugin1);
    plugin2->del_instance(plugin2);
    plugin3->del_instance(plugin3);
    plugin4->del_instance(plugin4);
    plugin5->del_instance(plugin5);
    plugin6->del_instance(plugin6);
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Xpoweramps::init_dsp_(uint32_t rate)
{
    plugin0->init(rate);
    plugin1->init(rate);
    plugin2->init(rate);
    plugin3->init(rate);
    plugin4->init(rate);
    plugin5->init(rate);
    plugin6->init(rate);
    // set values for internal ramping
    ramp_down_step = 32 * (256 * rate) / 48000; 
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
}

// connect the Ports used by the plug-in class
void Xpoweramps::connect_(uint32_t port,void* data)
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
            sel = static_cast<float*>(data);
            break;
        default:
            break;
    }
}

void Xpoweramps::activate_f()
{
    // allocate the internal DSP mem
}

void Xpoweramps::clean_up()
{
    // delete the internal DSP mem
}

void Xpoweramps::deactivate_f()
{
    // delete the internal DSP mem
}

void Xpoweramps::run_dsp_(uint32_t n_samples)
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
    if (sel_ != static_cast<uint32_t>(*(sel))) {
        if (!bypassed) {
            needs_ramp_down = true;
            needs_ramp_up = true;
        }
    }

    if (needs_ramp_down || needs_ramp_up) {
         memcpy(buf0, input0, n_samples*sizeof(float));
    }

    if (!bypassed) {
        switch ((int)sel_) {
            case 0:
                plugin2->compute(n_samples, output0, output0);
                break;
            case 1:
                plugin3->compute(n_samples, output0, output0);
                break;
            case 2:
                plugin5->compute(n_samples, output0, output0);
                break;
             case 3:
                plugin0->compute(n_samples, output0, output0);
                break;
             case 4:
                plugin1->compute(n_samples, output0, output0);
                break;
            case 5:
                plugin4->compute(n_samples, output0, output0);
                break;
            default:
                break;
        }
        plugin6->compute(n_samples, output0, output0);
    }
    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_down > 0.0) {
                --ramp_down; 
            }
            fade = max(0.0f,ramp_down) /ramp_down_step ;
            output0[i] = output0[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_down <= 0.0) {
            // when ramped down, clear buffer from dsp
            bypassed = true;
            plugin0->clear_state_f();
            plugin1->clear_state_f();
            plugin2->clear_state_f();
            plugin3->clear_state_f();
            plugin4->clear_state_f();
            plugin5->clear_state_f();
            plugin6->clear_state_f();
            needs_ramp_down = false;
            //now, when ramped down, change the model
            sel_ = static_cast<uint32_t>(*(sel));
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

void Xpoweramps::connect_all__ports(uint32_t port, void* data)
{
    // connect the Ports used by the plug-in class
    connect_(port,data); 
    plugin0->connect(port,data);
    plugin1->connect(port,data);
    plugin2->connect(port,data);
    plugin3->connect(port,data);
    plugin4->connect(port,data);
    plugin5->connect(port,data);
    plugin6->connect(port,data);
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Xpoweramps::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
    // init the plug-in class
    Xpoweramps *self = new Xpoweramps();
    if (!self) {
        return NULL;
    }
    self->init_dsp_((uint32_t)rate);
    return (LV2_Handle)self;
}

void Xpoweramps::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
    // connect all ports
    static_cast<Xpoweramps*>(instance)->connect_all__ports(port, data);
}

void Xpoweramps::activate(LV2_Handle instance)
{
    // allocate needed mem
    static_cast<Xpoweramps*>(instance)->activate_f();
}

void Xpoweramps::run(LV2_Handle instance, uint32_t n_samples)
{
    // run dsp
    static_cast<Xpoweramps*>(instance)->run_dsp_(n_samples);
}

void Xpoweramps::deactivate(LV2_Handle instance)
{
    // free allocated mem
    static_cast<Xpoweramps*>(instance)->deactivate_f();
}

void Xpoweramps::cleanup(LV2_Handle instance)
{
    // well, clean up after us
    Xpoweramps* self = static_cast<Xpoweramps*>(instance);
    self->clean_up();
    delete self;
}

const LV2_Descriptor Xpoweramps::descriptor =
{
    PLUGIN_URI ,
    Xpoweramps::instantiate,
    Xpoweramps::connect_port,
    Xpoweramps::activate,
    Xpoweramps::run,
    Xpoweramps::deactivate,
    Xpoweramps::cleanup,
    NULL
};

} // end namespace poweramps

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index)
    {
        case 0:
            return &poweramps::Xpoweramps::descriptor;
        default:
            return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
