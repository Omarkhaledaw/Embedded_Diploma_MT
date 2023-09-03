#include <stdio.h>
#include <math.h>


int main(){

	unsigned int num1,temp;

	printf("Welcome to Exercise 8 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);
	temp=sqrt(num1*num1);

	if(temp == num1){
		printf("The number you've entered is a perfect square..!!!");
	}else{
		printf("The number you've entered is not a perfect square...");
	}

	return 0;
}
