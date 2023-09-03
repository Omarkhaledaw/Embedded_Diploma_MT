#include <stdio.h>

int countOnes(unsigned char);

int main(){

	unsigned char num = 0b10011010;
	int result;
	printf("Welcome to Exercise 15 program, Please wait.\n");
	result = countOnes(num);
	printf("%d",result);

	return 0;
}
int countOnes(unsigned char num){
	unsigned char mask = 0b10000000;
	int count = 0;
	for(int i =0;i<8;i++){
		if((num<<i)& mask){
			count++;
		}
	}
	return count;
}
