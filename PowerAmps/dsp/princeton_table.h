
// princeton_table generated by DK/circ_table_gen.py -- do not modify manually

 // variables used
 // --sig_max  1.400000
 // --table_div  1.485639
 // --table_op  1.000000

struct tableprinceton { // 1-dimensional function table
    float low;
    float high;
    float istep;
    int size;
    float data[];
};

template <int tab_size>
struct tableprinceton_imp {
    float low;
    float high;
    float istep;
    int size;
    float data[tab_size];
    operator tableprinceton&() const { return *(tableprinceton*)this; }
};

 static tableprinceton_imp<200> princeton_table __rt_data = {
	0,0.833333,142.143,200, {
	0.000000000000,0.026283057516,0.051128857394,0.074661704863,0.096982209454,
	0.118186711354,0.138359957032,0.157578125771,0.175909906003,0.193417403731,
	0.210156927231,0.226179657639,0.241532228169,0.256257225772,0.270393627087,
	0.283977178645,0.297040729543,0.309614523286,0.321726454899,0.333402297663,
	0.344665903920,0.355539383219,0.366043260910,0.376196619366,0.386017224384,
	0.395521638262,0.404725321476,0.413642723890,0.422287367195,0.430671919138,
	0.438808260840,0.446707547632,0.454380264393,0.461836275762,0.469084871933,
	0.476134810461,0.482994354207,0.489671306320,0.496173042151,0.502506538493,
	0.508678400478,0.514694886301,0.520561929949,0.526285162219,0.531869929984,
	0.537321314185,0.542644146214,0.547843023346,0.552922322804,0.557886215031,
	0.562738675770,0.567483497512,0.572124299997,0.576664540096,0.581107520893,
	0.585456400358,0.589714199133,0.593883808168,0.597967995589,0.601969413242,
	0.605890602793,0.609734001454,0.613501947360,0.617196684594,0.620820367881,
	0.624375067121,0.627862771481,0.631285393356,0.634644772111,0.637942677514,
	0.641180813076,0.644360819108,0.647484275677,0.650552705381,0.653567575946,
	0.656530302719,0.659442250951,0.662304738097,0.665119035835,0.667886372116,
	0.670607932990,0.673284864434,0.675918274027,0.678509232562,0.681058775568,
	0.683567904774,0.686037589481,0.688468767874,0.690862348309,0.693219210399,
	0.695540206283,0.697826161596,0.700077876568,0.702296126936,0.704481664950,
	0.706635220220,0.708757500556,0.710849192854,0.712910963782,0.714943460579,
	0.716947311742,0.718923127722,0.720871501547,0.722793009467,0.724688211523,
	0.726557652184,0.728401860786,0.730221352111,0.732016626926,0.733788172388,
	0.735536462553,0.737261958820,0.738965110304,0.740646354285,0.742306116618,
	0.743944828143,0.745562860260,0.747160623283,0.748738500745,0.750296866650,
	0.751836085470,0.753356512630,0.754858494690,0.756342369664,0.757808467322,
	0.759257109346,0.760688609610,0.762103274528,0.763501403070,0.764883287193,
	0.766249211936,0.767599455602,0.768934290024,0.770253980736,0.771558787204,
	0.772848962799,0.774124755299,0.775386406704,0.776634153710,0.777868227589,
	0.779088854555,0.780296255744,0.781490647471,0.782672241340,0.783841244278,
	0.784997858764,0.786142282939,0.787274710710,0.788395331834,0.789504332020,
	0.790601893138,0.791688193238,0.792763406605,0.793827703930,0.794881252446,
	0.795924215891,0.796956754702,0.797979026059,0.798991183948,0.799993379279,
	0.800985759999,0.801968470983,0.802941654396,0.803905449474,0.804859992847,
	0.805805418408,0.806741857472,0.807669438861,0.808588288844,0.809498531358,
	0.810400287948,0.811293677890,0.812178818196,0.813055823679,0.813924807018,
	0.814785878855,0.815639147680,0.816484720126,0.817322700749,0.818153192305,
	0.818976295600,0.819792109701,0.820600731887,0.821402257645,0.822196780771,
	0.822984393521,0.823765186333,0.824539248198,0.825306666547,0.826067527193,
	0.826821914580,0.827569911660,0.828311599899,0.829047059451,0.829776369108,
	0.830499606231,0.831216846990,0.831928166245,0.832633637549,0.833333333324
	}
};

double always_inline princetonclip(double x) {
    double f = fabs(x);
    f = f * princeton_table.istep;
    int i = static_cast<int>(f);
    if (i < 0) {
        f = princeton_table.data[0];
    } else if (i >= princeton_table.size-1) {
        f = princeton_table.data[princeton_table.size-1];
    } else {
    f -= i;
    f = princeton_table.data[i]*(1-f) + princeton_table.data[i+1]*f;
    }
    return copysign(f, x);
}
