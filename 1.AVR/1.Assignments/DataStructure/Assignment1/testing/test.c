#include <stdio.h>

int zero_max(unsigned int);
int main(){
	unsigned int output;
	unsigned int num = 0b10100010000101000001100010100011;
	output = zero_max(num);
	printf("%d",output);

	return 0;
}
int zero_max(unsigned int num){
	unsigned int mask = 0b10000000000000000000000000000000;
	int consec =0,count=0;
	for(int i =0;i<32;i++){
		if(num & (mask>>i)){
			if(consec < count){
				consec = count;
			}
			count = 0;
		}else{
			count++;
		}
	}
	return consec;
}
