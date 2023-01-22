// generated from file '/home/brummer/projecte/PowerAmps/orangedarkterror.dsp' by dsp2cc:
// Code generated with Faust 2.50.6 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

#include "math.h"
#include "orangedarkterrorp3_neg_table.h"
#include "orangedarkterrorp3_table.h"

namespace orangedarkterror {

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
	double fConst1 = 1.86957288162412e-19 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (fConst1 + -6.82010407286301e-17) + 4.53454013961264e-15) + -6.51104139918237e-14) + 4.73642640396319e-17;
	double fConst3 = 7.47829152649647e-19 * fConst0;
	double fConst4 = mydsp_faustpower2_f(fConst0);
	fConst5 = fConst0 * (fConst4 * (1.3640208145726e-16 - fConst3) + -1.30220827983647e-13) + 1.89457056158527e-16;
	fConst6 = fConst4 * (1.12174372897447e-18 * fConst4 + -9.06908027922528e-15) + 2.84185584237791e-16;
	fConst7 = fConst0 * (fConst4 * (-1.3640208145726e-16 - fConst3) + 1.30220827983647e-13) + 1.89457056158527e-16;
	fConst8 = 1.0 / (fConst0 * (fConst0 * (fConst0 * (fConst1 + 6.82010407286301e-17) + 4.53454013961264e-15) + 6.51104139918237e-14) + 4.73642640396319e-17);
	double fConst9 = 6.57377333665727e-19 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (4.01607201070155e-17 - fConst9) + -4.37865590304316e-21) + -1.22291757237028e-24);
	double fConst11 = 2.62950933466291e-18 * fConst0;
	fConst12 = fConst0 * (fConst4 * (fConst11 + -8.03214402140309e-17) + -2.44583514474056e-24);
	fConst13 = fConst4 * (8.75731180608631e-21 - 3.94426400199436e-18 * fConst4);
	fConst14 = fConst4 * (fConst11 + 8.03214402140309e-17) + 2.44583514474056e-24;
	fConst15 = fConst0 * (fConst0 * (-4.01607201070155e-17 - fConst9) + -4.37865590304316e-21) + 1.22291757237028e-24;
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
		output0[i0] = FAUSTFLOAT(0.6 * fRec2[0] * ((signbit(fTemp0)) ? orangedarkterrorp3_negclip(fTemp0) : orangedarkterrorp3clip(fTemp0)));
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
} // end namespace orangedarkterror
