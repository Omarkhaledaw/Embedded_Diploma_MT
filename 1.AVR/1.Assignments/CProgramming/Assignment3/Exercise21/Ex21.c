#include <stdio.h>

int* reverseInclusive(unsigned int lowerValue,unsigned int upperValue,int *size);
int g_array[256];

int main(){
	unsigned int upper,lower;
	int size;
	printf("Welcome to Exercise 21 Program, please enter the lower value: ");
	fflush(stdout);
	scanf("%u",&lower);
	printf("Great, now enter the upper value: ");
	fflush(stdout);
	scanf("%u",&upper);

	reverseInclusive(lower,upper,&size);
	printf("\nOutput Array = ");
	for(int i =0;i<size;i++){
		printf("%u, ",g_array[i]);
	}
	printf("\nOutput Array size = %d",size);


	return 0;
}
int* reverseInclusive(unsigned int lowerValue,unsigned int upperValue,int *size){
	if(upperValue<lowerValue){
		g_array[0] = 0xFF;
		g_array[1] = 0xFF;
		*size = 2;
	}else{
		int range = upperValue-lowerValue+1;
		for(int i  = 0;i<range;i++){

			g_array[i] = upperValue;
			upperValue -=1;

		}
		*size = range;
	}


	return g_array;
}
