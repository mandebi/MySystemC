#include "systemc.h"
#define  WIDTH 16
#define VEC_SIZE 5

const sc_uint<WIDTH> coef [VEC_SIZE] = {18,77,107,77,18}; //fir coefficient

void fir::fir_main(){//fir main thread
	sc_int<WIDTH> vec [VEC_SIZE]; //shift register
	
    //reset code
    dataOut.write(0);
     
    wait(); //wait for 1 clock cycle

    while(true){//the only way to leave the loop is when the rst is asserted
	   for(int i = (VEC_SIZE - 1); i > 0; i--){
	       vec[i] = vec[i-1];	
	   }
		
	   vec[0] = dataIn.read();	
	   
	   sc_int<WIDTH> temp_val;
	   
	   for(int i=0; i <VEC_SIZE; i++){
	          temp_val += coef[i] * vec[i];
	          cout<<"@"<<sc_time_stamp() << "temp_val = "<< temp_val<<" ";
	          cout<<"    vec["<<i<<"] = "<<vec[i]<<endl;
	   }
	   dataOut.write(temp_val);
	   wait();
	} 
}
