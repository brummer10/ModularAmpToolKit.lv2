// generated from file 'tone.dsp' by dsp2cc:
// Code generated with Faust 2.54.9 (https://faust.grame.fr)

#include <cmath>

#define FAUSTFLOAT float

namespace tone {

class Dsp {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fRec1[2];


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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 2.11763955065454e-05 * fConst0;
	fConst2 = fConst1 + -0.0617027841099808;
	fConst3 = 8.95963520160933e-06 * fConst0;
	fConst4 = -0.0617027841099808 - fConst1;
	fConst5 = 3.01356397593146e-05 * fConst0;
	clear_state_f();
}

void Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
	double fSlow0 = 0.007000000000000006 * (1.0 - double(fVslider0));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		double fTemp0 = fConst2 * fRec0[0];
		double fTemp1 = fConst3 + fTemp0 + 0.0925554102206533;
		double fTemp2 = fConst4 * fRec0[0];
		fRec1[0] = double(input0[i0]) + (1e-15 - fRec1[1] * (fTemp2 + 0.0925554102206533 - fConst3) / fTemp1);
		output0[i0] = FAUSTFLOAT((fRec1[0] * (fTemp0 + -0.0308513920549904 - fConst5) + fRec1[1] * (fConst5 + fTemp2 + -0.0308513920549904)) / fTemp1);
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
	}
#undef fVslider0
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case 4: 
		fVslider0_ = static_cast<float*>(data); // , 0.5, 0.0, 1.0, 0.01 
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
} // end namespace tone
