// generated from file '/home/brummer/projecte/PowerAmps/supersonic.dsp' by dsp2cc:
// Code generated with Faust 2.50.6 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

#include "math.h"
#include "supersonic_neg_table.h"
#include "supersonic_table.h"

namespace supersonic {

class Dsp {
private:
	uint32_t fSampleRate;
	double fConst2;
	double fConst4;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec1[2];
	double fRec0[6];
	double fConst11;
	double fConst13;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
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
	for (int l1 = 0; l1 < 6; l1 = l1 + 1) fRec0[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec2[l2] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 5.00590822563103e-27 * fConst0;
	fConst2 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.85439561729349e-19 - fConst1) + -1.29213045864058e-16) + 1.91675735640238e-14) + -9.77706930886932e-13) + 1.59787065310447e-11;
	double fConst3 = 2.50295411281552e-26 * fConst0;
	fConst4 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst3 + -5.56318685188047e-19) + 1.29213045864058e-16) + 1.91675735640238e-14) + -2.9331207926608e-12) + 7.98935326552235e-11;
	double fConst5 = 5.00590822563103e-26 * fConst0;
	fConst6 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (3.70879123458698e-19 - fConst5) + 2.58426091728115e-16) + -3.83351471280476e-14) + -1.95541386177386e-12) + 1.59787065310447e-10;
	fConst7 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst5 + 3.70879123458698e-19) + -2.58426091728115e-16) + -3.83351471280476e-14) + 1.95541386177386e-12) + 1.59787065310447e-10;
	fConst8 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-5.56318685188047e-19 - fConst3) + -1.29213045864058e-16) + 1.91675735640238e-14) + 2.9331207926608e-12) + 7.98935326552235e-11;
	fConst9 = 1.0 / (fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst1 + 1.85439561729349e-19) + 1.29213045864058e-16) + 1.91675735640238e-14) + 9.77706930886932e-13) + 1.59787065310447e-11);
	double fConst10 = 2.20682184684432e-26 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (8.17344554235261e-19 - fConst10) + -1.15906710571025e-16) + 4.2235930719266e-15) + -7.76975700660911e-14) + 1.26979539981828e-12;
	double fConst12 = 1.10341092342216e-25 * fConst0;
	fConst13 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst12 + -2.45203366270578e-18) + 1.15906710571025e-16) + 4.2235930719266e-15) + -2.33092710198273e-13) + 6.34897699909141e-12;
	double fConst14 = 2.20682184684432e-25 * fConst0;
	fConst15 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (1.63468910847052e-18 - fConst14) + 2.31813421142051e-16) + -8.44718614385319e-15) + -1.55395140132182e-13) + 1.26979539981828e-11;
	fConst16 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst14 + 1.63468910847052e-18) + -2.31813421142051e-16) + -8.44718614385319e-15) + 1.55395140132182e-13) + 1.26979539981828e-11;
	fConst17 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (-2.45203366270578e-18 - fConst12) + -1.15906710571025e-16) + 4.2235930719266e-15) + 2.33092710198273e-13) + 6.34897699909141e-12;
	fConst18 = fConst0 * (fConst0 * (fConst0 * (fConst0 * (fConst10 + 8.17344554235261e-19) + 1.15906710571025e-16) + 4.2235930719266e-15) + 7.76975700660911e-14) + 1.26979539981828e-12;
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
		fRec0[0] = double(input0[i0]) * fRec1[0] - fConst9 * (fConst8 * fRec0[1] + fConst7 * fRec0[2] + fConst6 * fRec0[3] + fConst4 * fRec0[4] + fConst2 * fRec0[5]);
		double fTemp0 = fConst9 * (fConst18 * fRec0[0] + fConst17 * fRec0[1] + fConst16 * fRec0[2] + fConst15 * fRec0[3] + fConst13 * fRec0[4] + fConst11 * fRec0[5]);
		fRec2[0] = fSlow1 + 0.999 * fRec2[1];
		output0[i0] = FAUSTFLOAT(0.8 * fRec2[0] * ((signbit(fTemp0)) ? supersonic_negclip(fTemp0) : supersonicclip(fTemp0)));
		fRec1[1] = fRec1[0];
		for (int j0 = 5; j0 > 0; j0 = j0 - 1) {
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
} // end namespace supersonic
