#include "systemc.h"
#define WIDTH 4
#define DEBUG 0

SC_MODULE(adder){
 sc_in<bool> dataIn;
 sc_in<sc_uint<WIDTH> > opA;
 sc_in<sc_uint<WIDTH> > opB;
 sc_out<sc_uint<2*WIDTH> > result;
 
 void add(){
	if(DEBUG) 
	   cout << "   *** Add function- received opA="<<opA<< " and opB="<<opB<<endl; 
    if(dataIn.read() == 1)//there is new incoming inputs
        result.write(opA.read() + opB.read());
    else
        result.write(0);
 }


 SC_CTOR(adder){
   cout << "Constructor of the SC_MODULE 'adder'"<<endl;	 
   SC_METHOD(add);
   sensitive << dataIn;
 }//end of constructor
 
};//end of the module "adder"
