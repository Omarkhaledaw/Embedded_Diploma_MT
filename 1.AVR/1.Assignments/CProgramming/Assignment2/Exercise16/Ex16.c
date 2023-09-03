#include <stdio.h>

int countOnes(unsigned int);

int main(){

	unsigned int num = 0x00000FFF;
	int result;
	printf("Welcome to Exercise 16 program, Please wait.\n");
	result = countOnes(num);
	printf("%d",result);

	return 0;
}
int countOnes(unsigned int num){
	unsigned int mask = 0x80000000;
	int count = 0;
	for(int i =0;i<32;i++){
		if((num<<i)& mask){
			count++;
		}
	}
	return count;
}
