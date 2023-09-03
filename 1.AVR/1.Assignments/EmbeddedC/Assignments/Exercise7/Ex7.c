#include <stdio.h>

void clearBit(int *,int);

int main(){
	int num,bit;

	printf("Welcome to Exercise 7 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	printf("Great now enter the bit number you'd like to clear: ");
	fflush(stdout);
	scanf("%d",&bit);

	clearBit(&num,bit);

	printf("Your number is now %d",num);

	return 0;
}
void clearBit(int *num,int bit){
	if(bit>7){
		printf("ERROR 404!");
	}else{
	*num = *num & ~(1<<bit);
	}
}
