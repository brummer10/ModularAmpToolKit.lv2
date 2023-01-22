// generated from file '/home/brummer/projecte/PowerAmps/epiphone.dsp' by dsp2cc:
// Code generated with Faust 2.50.6 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

#include "epiphone_jr_out_neg_table.h"
#include "epiphone_jr_out_table.h"
#include "math.h"

namespace epiphone {

class Dsp {
private:
	uint32_t fSampleRate;
	double fConst2;
	double fConst4;
	double fConst5;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fRec0[3];
	double fConst7;
	double fConst8;
	double fConst9;
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
	for (int l1 = 0; l1 < 3; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 4.33069857761234e-10 * fConst0;
	fConst2 = fConst0 * (fConst1 + -4.59724862995143e-08) + 3.68375740341601e-07;
	double fConst3 = mydsp_faustpower2_f(fConst0);
	fConst4 = 7.36751480683202e-07 - 8.66139715522468e-10 * fConst3;
	fConst5 = 1.0 / (fConst0 * (fConst1 + 4.59724862995143e-08) + 3.68375740341601e-07);
	double fConst6 = 5.16589926047446e-10 * fConst0;
	fConst7 = fConst0 * (fConst6 + -5.33527722168907e-08);
	fConst8 = 0.0 - 1.03317985209489e-09 * fConst3;
	fConst9 = fConst0 * (fConst6 + 5.33527722168907e-08);
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
		fRec0[0] = double(input0[i0]) * fRec1[0] - fConst5 * (fConst4 * fRec0[1] + fConst2 * fRec0[2]);
		double fTemp0 = fConst5 * (fConst9 * fRec0[0] + fConst8 * fRec0[1] + fConst7 * fRec0[2]);
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		output0[i0] = FAUSTFLOAT(2.0 * fRec2[0] * ((signbit(fTemp0)) ? epiphone_jr_out_negclip(fTemp0) : epiphone_jr_outclip(fTemp0)));
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
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
} // end namespace epiphone
