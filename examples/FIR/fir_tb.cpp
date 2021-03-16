#include "systemc.h"
#include "fir.cpp"
#include "fir_main.cpp"
#define  WIDTH 16

int sc_main(int argc, char* argv[]){
 //signals driving the DUT
 sc_signal<bool> clk;
 sc_signal<bool> rst;
 sc_signal < sc_int<WIDTH> > dataIn;
 sc_signal < sc_int<WIDTH> > dataOut;
 
 //DUT instantiation
 fir f("FIR");
 f.clk(clk);
 f.rst(rst);
 f.dataIn(dataIn);
 f.dataOut(dataOut);
 
 
 sc_time t1(1,SC_PS); 
 sc_start(t1);
 
 //Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("fir");
    
 //Dump the desired signals
    sc_trace(wf,clk,"clk");
    sc_trace(wf,rst,"rst");
    sc_trace(wf,dataIn,"dataIn");
    sc_trace(wf,dataOut,"dataOut");
    
 //Now we provide values into input signals
    rst = 1;
    dataIn = 2;
    
    for(int i=0;i<5;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}
	
	rst = 0;
    
    for(int i=0;i<5;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}

}
