#include <stdio.h>

unsigned char RightCircularShift(unsigned int,int,unsigned int *);

int main(){
	unsigned int num = 255;
	unsigned int output,result;
	result = RightCircularShift(num,2,&output);
	printf("Result = %x",result);


	return 0;
}
unsigned char RightCircularShift(unsigned int InputNumber, int NumberOfShifts, unsigned int * pOutput){

	if(NumberOfShifts > 8*sizeof(InputNumber)){
		*pOutput = InputNumber;
		return 0xFF;
	}else{
		*pOutput = ((InputNumber >> NumberOfShifts) | (InputNumber << (8*sizeof(InputNumber)-NumberOfShifts)));
		return 0;
	}
}
