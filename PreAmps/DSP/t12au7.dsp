declare id "12AU7"; // in amp tube ba.selector
declare name "12AU7";

import("stdfaust.lib"); 
import("tubes.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) = stage1 : stage2 with {

    stage1 =  *(preamp):*(4.0): tubestage(TB_12AU7_68k,86.0,2700.0,3.718962) :
    fi.lowpass(1,6531.0) : tubestage(TB_12AU7_250k,132.0,1500.0,2.314844):*(4.0) ; 
    stage2 = fi.lowpass(1,6531.0) : tubestage(TB_12AU7_250k,194.0,820.0,1.356567) : *(gain1):*(4.0); 

} ;

process =  tubeax(preamp,gain1) with {
    preamp =  vslider("Gain", 0,-20,20,0.1) : ba.db2linear : si.smooth(0.999);
    gain1 = vslider("Volume", 0, -20.0, 20.0, 0.1) : ba.db2linear : si.smooth(0.999);
};
