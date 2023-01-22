// generated from file '/home/brummer/projecte/PowerAmps/PreAmps/fizz_remover.dsp' by dsp2cc:
// Code generated with Faust 2.54.9 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

namespace fizz_remover {

class Dsp {
private:
	uint32_t fSampleRate;
	double fConst2;
	double fConst6;
	double fConst7;
	double fRec0[3];
	double fConst9;
	double fConst10;


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
	for (int l0 = 0; l0 < 3; l0 = l0 + 1) fRec0[l0] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = std::tan(17454.68878334489 / fConst0);
	fConst2 = 2.0 * (1.0 - 1.0 / mydsp_faustpower2_f(fConst1));
	double fConst3 = fConst0 * std::sin(34909.37756668978 / fConst0);
	double fConst4 = 5463.779747862935 / fConst3;
	double fConst5 = 1.0 / fConst1;
	fConst6 = (fConst5 - fConst4) / fConst1 + 1.0;
	fConst7 = 1.0 / ((fConst5 + fConst4) / fConst1 + 1.0);
	double fConst8 = 2053.4927980405755 / fConst3;
	fConst9 = (fConst5 - fConst8) / fConst1 + 1.0;
	fConst10 = (fConst5 + fConst8) / fConst1 + 1.0;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = fConst2 * fRec0[1];
		fRec0[0] = double(input0[i0]) - fConst7 * (fConst6 * fRec0[2] + fTemp0);
		output0[i0] = FAUSTFLOAT(fConst7 * (fTemp0 + fConst10 * fRec0[0] + fConst9 * fRec0[2]));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
	}
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
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
} // end namespace fizz_remover
