#include "systemc.h"

SC_MODULE(counter){
	
	sc_in_clk clk ;//input clock
	sc_in<bool> reset; //active high, synchronuous, it resets the input
	sc_in<bool> enable; //active high enable signal for counter
	sc_out<sc_uint<4> > counter_out;//4-bit vector that is the output of the counter logic

    //local signal
    sc_uint<4> count; 
 
    void counter_logic(){
		if(reset.read() == 1){//system if a reset mode 
			count = 0;
		    counter_out.write(count);	 
		 }
		else{
			
			if(enable.read()==1){//here we can count up
			   count = count + 1;
			   counter_out.write(count);
			   cout<< "@" << sc_time_stamp() << ":: Incremented Counter " << counter_out.read() << endl;
		    }
			
	    } 
	}// end "counter_logic()" function 


    SC_CTOR(counter){
	   cout<< "Instantiating the counter logic ..."<<endl;
	   SC_METHOD(counter_logic);
	   sensitive << reset;
	   sensitive << clk.pos();
	}//end of constructor
	
	
	
	void test_function(){
	  cout<< "Counter ready to start ..."<<endl;
	}

};
