#include "systemc.h"
#include "adder.cpp"
#include <cmath>
#define WIDTH 4
#define DEBUG 0

int sc_main(int argc, char* argv[]){
 sc_signal<bool> clk;	 
 sc_buffer <bool> dataIn;
 sc_signal<sc_uint<WIDTH> > opA;
 sc_signal<sc_uint<WIDTH> > opB;
 sc_signal<sc_uint<2*WIDTH> > result;
  
  //local variable
  int success;
 //DUT instantiation 
 adder DUT("adder");
 DUT.dataIn(dataIn); 
 DUT.opA(opA);
 DUT.opB(opB);
 DUT.result(result);


 //Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("adder");
    
 //Dump the desired signals
	sc_trace(wf,clk,"clk");
	sc_trace(wf,dataIn,"dataIn");
	sc_trace(wf,opA,"opA");
	sc_trace(wf,opB,"opB"); 
	sc_trace(wf,result,"result"); 
 
 //Here we feed inputs to the DUT
 sc_time t1(1,SC_PS);
 sc_start(t1);
 
  cout<<"\n\n  #### TEST CASE 1 #### "<<endl;
 //testing that additions only start when the "dataIn" signal is asserted
 success = 1;
 for(int i=0; i<pow(2,(WIDTH )); i++)
  for(int j=0; j<pow(2,(WIDTH)); j++){
	    
	    clk = 0;
	    sc_start(t1);
	    clk = 1;
	    sc_start(t1);	
	
	    opA=i; 
	    opB=j;
	    dataIn=0;

	    if(result.read() != 0){
	      cout<<"@" << sc_time_stamp() << "[TEST FAILED] " <<opA.read()<< " + "<<opB.read()<< " = "<<result.read()<<" instead of 0 when dataIn = 0"<<endl;
	      success = 0;
	    }
	    else
	     if(DEBUG)
	       cout<<"@" << sc_time_stamp() << "[TEST PASSED] " <<opA.read()<< " + "<<opB.read()<< " = 0 when dataIn = 0"<<endl;     
  }
  
  if(success == 1)
    cout<<"TEST CASE SUCCESSFUL !"<<endl;
  else
    cout<<"TEST CASE FAILURE !"<<endl;
  
  clk = 0;
  sc_start(t1);
  clk = 1;
  sc_start(t1);
  opA=0; 
  opB=0;
 
 cout<<"\n\n  #### TEST CASE 2 #### "<<endl;
  success = 1;
 //testing all possible additions on WIDTH number of bits
 for(int i=0; i<pow(2,(WIDTH)); i++)
  for(int j=0; j<pow(2,(WIDTH)); j++){
 
	   clk = 0;
	   sc_start(t1);
	   clk = 1;
	   sc_start(t1);	
	    
	    opA = i;
	    opB = j;
	    dataIn = 1;
	    
	    if(result.read() != opA.read()+opB.read()){
	      cout<<"@" << sc_time_stamp() << "[TEST FAILED] " <<opA.read()<< " + "<<opB.read()<< " = "<<result.read()<<" instead of "<<opA.read()+opB.read()<<endl;
	      success = 0;
	    }
	    else
	      if(DEBUG)
	         cout<<"@" << sc_time_stamp() << "[TEST PASSED] " <<opA.read()<< " + "<<opB.read()<< " = "<<result.read()<<endl;     
  }
 
 
 if(success == 1)
    cout<<"TEST CASE SUCCESSFUL !"<<endl;
  else
    cout<<"TEST CASE FAILURE !"<<endl;
 
 sc_close_vcd_trace_file(wf);
 

 return 0;
}//end of the testbench
