declare id "12AT7"; // in amp tube ba.selector
declare name "12AT7";

import("stdfaust.lib"); 
import("tubes.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 *         12AT7
 */
 

tubeax(preamp,gain1) = stage1 : stage2 with {
          
    stage1 = *(preamp) : tubestage(TB_12AT7_68k,86.0,2700.0,2.617753) : 
    fi.lowpass(1,6531.0) : tubestage(TB_12AT7_250k,132.0,1500.0,1.887332) ; 
    stage2 = fi.lowpass(1,6531.0) : tubestage(TB_12AT7_250k,194.0,820.0,1.256962) : *(gain1); 
    
};

process = tubeax(preamp,gain1) with {
    preamp =  vslider("Gain", 0,-20,20,0.1) : ba.db2linear : si.smooth(0.999);
    gain1 = vslider("Volume", 0, -20.0, 20.0, 0.1) : ba.db2linear : si.smooth(0.999);
};
