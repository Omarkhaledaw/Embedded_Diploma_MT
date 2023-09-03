#include <stdio.h>

int consecOnes(unsigned int);

int main(){

	unsigned int num = 0b1001111001110001;
	int result;
	printf("Welcome to Exercise 20 program\n");
	result = consecOnes(num);
	printf("%d",result);

	return 0;
}
int consecOnes(unsigned int num){
	int count = 0;
	int consec = 0;
	unsigned int mask = 0b1000000000000000;
	for(int i =0;i<16;i++){
		if((num<<i)& mask){
			count++;

		}else{
			if(consec >= count){
				count = 0;
			}else{
				consec = count;
			}
		}
	}
	return consec;
}
