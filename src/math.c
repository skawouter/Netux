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
