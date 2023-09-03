#include <stdio.h>

int forthBit(int num){
	return ((num & 0x00000008)>>3);
}

int main(){
	int result;
	int num = 23;
	result = forthBit(num);
	printf("The forth bit in %d is %d",num,result);
	return 0;
}
