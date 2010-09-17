#include "./include/math.h"

unsigned int expon( int nor, int expo ){
	int x;
	unsigned int returnvalue;
	returnvalue = nor;
	if (expo < 1){
		expo =1;}
	for (x=0; x < expo; x++)
	{
		returnvalue = returnvalue * nor;
	}
	return returnvalue;
}
long unsigned int doexpon(short number, short expon){
        short orignumber;
        long unsigned int result = number;
        orignumber = number;
        while(expon > 0){
                result = result * orignumber;
                expon--;
        }
        return result;
}
