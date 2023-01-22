// generated from file '/home/brummer/projecte/PowerAmps/PreAmps/t6DJ8.dsp' by dsp2cc:
// Code generated with Faust 2.54.9 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

#include "valve.h"

namespace t6dj8 {

class Dsp {
private:
	uint32_t fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fRec15[2];
	double fVec0[2];
	double fRec14[2];
	double fRec13[3];
	double fConst2;
	double fVec1[2];
	double fConst3;
	double fRec16[2];
	double fRec12[2];
	double fConst5;
	double fConst6;
	double fRec11[2];
	double fConst8;
	double fConst9;
	double fRec10[2];
	double fRec9[2];
	double fRec8[3];
	double fConst11;
	double fVec2[2];
	double fConst12;
	double fRec17[2];
	double fRec7[2];
	double fRec6[2];
	double fRec5[2];
	double fRec4[2];
	double fRec3[3];
	double fConst14;
	double fVec3[2];
	double fConst15;
	double fRec18[2];
	double fRec2[2];
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
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec15[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fVec0[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec14[l3] = 0.0;
	for (int l4 = 0; l4 < 3; l4 = l4 + 1) fRec13[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fVec1[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec16[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec12[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec11[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec10[l9] = 0.0;
	for (int l10 = 0; l10 < 2; l10 = l10 + 1) fRec9[l10] = 0.0;
	for (int l11 = 0; l11 < 3; l11 = l11 + 1) fRec8[l11] = 0.0;
	for (int l12 = 0; l12 < 2; l12 = l12 + 1) fVec2[l12] = 0.0;
	for (int l13 = 0; l13 < 2; l13 = l13 + 1) fRec17[l13] = 0.0;
	for (int l14 = 0; l14 < 2; l14 = l14 + 1) fRec7[l14] = 0.0;
	for (int l15 = 0; l15 < 2; l15 = l15 + 1) fRec6[l15] = 0.0;
	for (int l16 = 0; l16 < 2; l16 = l16 + 1) fRec5[l16] = 0.0;
	for (int l17 = 0; l17 < 2; l17 = l17 + 1) fRec4[l17] = 0.0;
	for (int l18 = 0; l18 < 3; l18 = l18 + 1) fRec3[l18] = 0.0;
	for (int l19 = 0; l19 < 2; l19 = l19 + 1) fVec3[l19] = 0.0;
	for (int l20 = 0; l20 < 2; l20 = l20 + 1) fRec18[l20] = 0.0;
	for (int l21 = 0; l21 < 2; l21 = l21 + 1) fRec2[l21] = 0.0;
	for (int l22 = 0; l22 < 2; l22 = l22 + 1) fRec1[l22] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = 1.0 / std::tan(270.1769682087222 / fConst0);
	fConst2 = 1.0 - fConst1;
	fConst3 = 1.0 / (fConst1 + 1.0);
	double fConst4 = 3.141592653589793 / fConst0;
	fConst5 = 1.0 - fConst4;
	fConst6 = 1.0 / (fConst4 + 1.0);
	double fConst7 = 1.0 / std::tan(20517.741620594938 / fConst0);
	fConst8 = 1.0 - fConst7;
	fConst9 = 1.0 / (fConst7 + 1.0);
	double fConst10 = 1.0 / std::tan(414.6902302738527 / fConst0);
	fConst11 = 1.0 - fConst10;
	fConst12 = 1.0 / (fConst10 + 1.0);
	double fConst13 = 1.0 / std::tan(609.4689747964198 / fConst0);
	fConst14 = 1.0 - fConst13;
	fConst15 = 1.0 / (fConst13 + 1.0);
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
	double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
	double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.999 * fRec0[1];
		fRec15[0] = fSlow1 + 0.999 * fRec15[1];
		double fTemp0 = double(input0[i0]) * fRec15[0];
		fVec0[0] = fTemp0;
		fRec14[0] = 0.9302847925323914 * (fTemp0 + fVec0[1]) - 0.8605695850647829 * fRec14[1];
		fRec13[0] = fRec14[0] - (1.8405051250752198 * fRec13[1] + 0.8612942439318627 * fRec13[2]);
		double fTemp1 = 1.8508996845035413 * fRec13[1];
		double fTemp2 = 0.9254498422517706 * (fRec13[0] + fRec13[2]);
		double fTemp3 = (fTemp1 + fTemp2) / (Ranode(TUBE_TABLE_6DJ8_68k, fRec12[1]) + 1e+05);
		fVec1[0] = fTemp3;
		fRec16[0] = fConst3 * (2.7e+03 * (fTemp3 + fVec1[1]) - fConst2 * fRec16[1]);
		fRec12[0] = Ftube(TUBE_TABLE_6DJ8_68k, fTemp2 + fRec16[0] + fTemp1 + -1.863946) + -60.96496296296296;
		fRec11[0] = fConst6 * (fConst5 * fRec11[1] + 0.05 * (fRec12[0] - fRec12[1]));
		fRec10[0] = 0.0 - fConst9 * (fConst8 * fRec10[1] - (fRec11[0] + fRec11[1]));
		fRec9[0] = 0.9302847925323914 * (fRec10[0] + fRec10[1]) - 0.8605695850647829 * fRec9[1];
		fRec8[0] = fRec9[0] - (1.8405051250752198 * fRec8[1] + 0.8612942439318627 * fRec8[2]);
		double fTemp4 = 1.8508996845035413 * fRec8[1];
		double fTemp5 = 0.9254498422517706 * (fRec8[0] + fRec8[2]);
		double fTemp6 = (fTemp4 + fTemp5) / (Ranode(TUBE_TABLE_6DJ8_250k, fRec7[1]) + 1e+05);
		fVec2[0] = fTemp6;
		fRec17[0] = fConst12 * (1.5e+03 * (fTemp6 + fVec2[1]) - fConst11 * fRec17[1]);
		fRec7[0] = Ftube(TUBE_TABLE_6DJ8_250k, fTemp5 + fRec17[0] + fTemp4 + -1.271609) + -45.22606666666667;
		fRec6[0] = fConst6 * (fConst5 * fRec6[1] + 0.05 * (fRec7[0] - fRec7[1]));
		fRec5[0] = 0.0 - fConst9 * (fConst8 * fRec5[1] - (fRec6[0] + fRec6[1]));
		fRec4[0] = 0.9302847925323914 * (fRec5[0] + fRec5[1]) - 0.8605695850647829 * fRec4[1];
		fRec3[0] = fRec4[0] - (1.8405051250752198 * fRec3[1] + 0.8612942439318627 * fRec3[2]);
		double fTemp7 = 1.8508996845035413 * fRec3[1];
		double fTemp8 = 0.9254498422517706 * (fRec3[0] + fRec3[2]);
		double fTemp9 = (fTemp7 + fTemp8) / (Ranode(TUBE_TABLE_6DJ8_68k, fRec2[1]) + 1e+05);
		fVec3[0] = fTemp9;
		fRec18[0] = fConst15 * (8.2e+02 * (fTemp9 + fVec3[1]) - fConst14 * fRec18[1]);
		fRec2[0] = Ftube(TUBE_TABLE_6DJ8_68k, fTemp8 + fRec18[0] + fTemp7 + -0.799031) + -32.55719512195121;
		fRec1[0] = fConst6 * (fConst5 * fRec1[1] + 0.05 * (fRec2[0] - fRec2[1]));
		output0[i0] = FAUSTFLOAT(fRec1[0] * fRec0[0]);
		fRec0[1] = fRec0[0];
		fRec15[1] = fRec15[0];
		fVec0[1] = fVec0[0];
		fRec14[1] = fRec14[0];
		fRec13[2] = fRec13[1];
		fRec13[1] = fRec13[0];
		fVec1[1] = fVec1[0];
		fRec16[1] = fRec16[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fVec3[1] = fVec3[0];
		fRec18[1] = fRec18[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
#undef fVslider0
#undef fVslider1
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fVslider1_ = static_cast<float*>(data); // , 0.0, -2e+01, 2e+01, 0.1 
		break;
	case VOLUME: 
		fVslider0_ = static_cast<float*>(data); // , 0.0, -2e+01, 2e+01, 0.1 
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
} // end namespace t6dj8
