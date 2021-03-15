#include "systemc.h"
#include "counter.cpp"

int sc_main(int argc, char*  argv[]){

 //signals that will drive the DUT
 sc_signal<bool> clk;
 sc_signal<bool> reset; //active high, synchronuous, it resets the input
 sc_signal<bool> enable; //active high enable signal for counter
 sc_signal<sc_uint<4> > counter_out;//4-bit vector that is the output of the counter logic

 int i = 0;
 
    //DUT instantiation
    counter count("COUNTER"); 
    count.clk(clk); 
    count.reset(reset);
    count.enable(enable);
    count.counter_out(counter_out);  
    
     sc_time             t1(1,SC_PS);
    
    sc_start(t1);
    
    //Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("counter");
    
    //Dump the desired signals
    sc_trace(wf,clk,"clk");
    sc_trace(wf,reset,"reset");
    sc_trace(wf,enable,"enable");
    sc_trace(wf,counter_out,"counter_out");
    
    //Now we provide values into input signals
    reset = 0;
    enable = 0;
    
    for(i=0;i<5;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}
	
	reset = 1; //assert the reset
	cout << "@" << sc_time_stamp() << " Asserting reset" << endl;
	for(i=0;i<10;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}
	
	reset = 0; //dassert the reset
	cout << "@" << sc_time_stamp() << " De-asserting reset" << endl;
	for(i=0;i<10;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}
	
	
	enable = 1; //enable counting up
	cout << "@" << sc_time_stamp() << " Asserting Enable" << endl;
	for(i=0;i<10;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}
	
	reset = 1; //asserting the reset
	cout << "@" << sc_time_stamp() << " Asserting reset" << endl;
	for(i=0;i<5;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}
	
	reset = 0; //deasserting the reset
	cout << "@" << sc_time_stamp() << " De-asserting reset" << endl;
	for(i=0;i<5;i++){
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	}     
	
	sc_close_vcd_trace_file(wf);
	
  return 0;
}
