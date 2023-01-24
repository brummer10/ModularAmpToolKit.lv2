declare id "6DJ8"; // in amp tube ba.selector
declare name "6DJ8";

import("stdfaust.lib"); 
import("tubes.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) = stage1 : stage2 with {
    stage1 = *(preamp) : tubestage130_20(TB_6DJ8_68k,86.0,2700.0,1.863946) : 
    fi.lowpass(1,6531.0) : tubestage130_20(TB_6DJ8_250k,132.0,1500.0,1.271609) ; 
    stage2 = fi.lowpass(1,6531.0) : tubestage130_20(TB_6DJ8_68k,194.0,820.0,0.799031) : *(gain1); 
    
} ;

process = tubeax(preamp,gain1) with {
    preamp =  vslider("Gain", 0,-20,20,0.1) : ba.db2linear : si.smooth(0.999);
    gain1 = vslider("Volume", 0, -20.0, 20.0, 0.1) : ba.db2linear : si.smooth(0.999);
};
