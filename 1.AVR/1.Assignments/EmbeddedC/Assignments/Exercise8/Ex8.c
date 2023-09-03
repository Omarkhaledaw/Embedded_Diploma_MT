#include <stdio.h>

unsigned char reverseBinary(unsigned char);
void printBinary(unsigned char);

int main(){
//	unsigned char num1 = 0b11010001;
//	unsigned char num2;
//	num2 = reverseBinary(num1);
//	printBinary(num2);
char s[2]={"12"};
int time = (s[0]-48)*10 + (s[1]-48);
printf("%d",time);
	return 0;
}
unsigned char reverseBinary(unsigned char num){
	int numberOfBits = sizeof(num);
	unsigned char result;
	for(int i = 0;i<numberOfBits;i++){
		if((num<<i)&1){
			result |= (1 << ((numberOfBits -1)-i));
		}
	}
	return result;
}
void printBinary(unsigned char num){

	int numberOfBits = sizeof(num);
	//unsigned char mask = 1;
	for(int i=0;i<numberOfBits;i++){
		if((num<<i) & 1){
			printf("1 ");
		}else{
			printf("0 ");
		}
	}
}
