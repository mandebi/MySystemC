#include "systemc.h"
#define  WIDTH 16

SC_MODULE(fir){
   sc_in<bool> clk;
   sc_in<bool> rst;
   sc_in < sc_int<WIDTH> > dataIn;
   sc_out < sc_int<WIDTH> > dataOut;
 
   void fir_main();

   SC_CTOR(fir){
    SC_CTHREAD(fir_main, clk.pos());
    reset_signal_is(rst, true);
   
   }

};
