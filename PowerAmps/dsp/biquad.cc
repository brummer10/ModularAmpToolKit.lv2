// generated from file '/home/brummer/projecte/PowerAmps/biquad.dsp' by dsp2cc:
// Code generated with Faust 2.54.9 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

namespace biquad {

class Dsp {
private:
	uint32_t fSampleRate;
	double fRec0[3];


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
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = double(input0[i0]) + 1.84 * fRec0[1] - 0.846416 * fRec0[2];
		output0[i0] = FAUSTFLOAT(0.31622776601683794 * (fRec0[0] - 1.01 * fRec0[1]));
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
} // end namespace biquad
