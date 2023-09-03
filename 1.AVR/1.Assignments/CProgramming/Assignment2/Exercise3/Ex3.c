#include <stdio.h>

void checkSign(int);

int main(){

	int num;
	printf("Welcome to Exercise 3 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	checkSign(num);

	return 0;
}
void checkSign(int num){
	if(num > 0){
		printf("The number you have entered is a positive number.");
	}else{
		printf("The number you have entered is a negative number.");
	}
}
