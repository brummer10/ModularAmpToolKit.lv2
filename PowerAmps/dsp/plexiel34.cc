// generated from file '/home/brummer/projecte/PowerAmps/plexiel34.dsp' by dsp2cc:
// Code generated with Faust 2.50.6 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

#include "math.h"
#include "plexipowerampel34_neg_table.h"
#include "plexipowerampel34_table.h"

namespace plexiel34 {

class Dsp {
private:
	uint32_t fSampleRate;
	double fConst0;
	double fConst2;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fRec0[5];
	double fConst10;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec2[2];


public:
	void connect(uint32_t port,void* data);
	void del_instance(Dsp *p);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	Dsp();
	~Dsp();
};



Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
	for (int l1 = 0; l1 < 5; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.82693733893894e-19 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (fConst1 + -2.71243523616587e-16) + 8.16290535602033e-14) + -4.64147298174261e-12) + 4.00158102875003e-12;
	double fConst3 = 7.30774935575574e-19 * fConst0;
	double fConst4 = mydsp_faustpower2_f(fConst0);
	fConst5 = fConst0 * (fConst4 * (5.42487047233173e-16 - fConst3) + -9.28294596348523e-12) + 1.60063241150001e-11;
	fConst6 = fConst4 * (1.09616240336336e-18 * fConst4 + -1.63258107120407e-13) + 2.40094861725002e-11;
	fConst7 = fConst0 * (fConst4 * (-5.42487047233173e-16 - fConst3) + 9.28294596348523e-12) + 1.60063241150001e-11;
	fConst8 = 1.0 / (fConst0 * (fConst0 * (fConst0 * (fConst1 + 2.71243523616587e-16) + 8.16290535602033e-14) + 4.64147298174261e-12) + 4.00158102875003e-12);
	double fConst9 = 3.87560926163844e-19 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst9 + -4.30800903120125e-16) + 3.17509705609174e-17) + -5.3495467261267e-19);
	double fConst11 = 1.55024370465538e-18 * fConst0;
	fConst12 = fConst0 * (fConst4 * (8.61601806240251e-16 - fConst11) + -1.06990934522534e-18);
	fConst13 = fConst4 * (2.32536555698307e-18 * fConst4 + -6.35019411218347e-17);
	fConst14 = fConst4 * (-8.61601806240251e-16 - fConst11) + 1.06990934522534e-18;
	fConst15 = fConst0 * (fConst0 * (fConst9 + 4.30800903120125e-16) + 3.17509705609174e-17) + 5.3495467261267e-19;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec1[0] = fSlow0 + 0.999 * fRec1[1];
		fRec0[0] = double(input0[i0]) * fRec1[0] - fConst8 * (fConst7 * fRec0[1] + fConst6 * fRec0[2] + fConst5 * fRec0[3] + fConst2 * fRec0[4]);
		double fTemp0 = fConst8 * (fConst0 * (fConst15 * fRec0[0] + fConst14 * fRec0[1]) + fConst13 * fRec0[2] + fConst12 * fRec0[3] + fConst10 * fRec0[4]);
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		output0[i0] = FAUSTFLOAT(fRec2[0] * ((signbit(fTemp0)) ? plexipowerampel34_negclip(fTemp0) : plexipowerampel34clip(fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec0[j0] = fRec0[j0 - 1];
		}
		fRec2[1] = fRec2[0];
	}
#undef fVslider0
#undef fVslider1
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fVslider0_ = static_cast<float*>(data); // , 0.0, -3e+01, 3e+01, 0.1 
		break;
	case VOLUME: 
		fVslider1_ = static_cast<float*>(data); // , 0.0, -3e+01, 3e+01, 0.1 
		break;
	default:
		break;
	}
}

Dsp *plugin() {
	return new Dsp();
}

void Dsp::del_instance(Dsp *p)
{
	delete p;
}
} // end namespace plexiel34
