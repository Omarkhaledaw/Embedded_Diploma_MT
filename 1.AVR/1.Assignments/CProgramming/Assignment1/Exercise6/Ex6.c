#include <stdio.h>



int main(){
	int num1,num2;
	printf("Welcome to Exercise 6 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);

	printf("Great! now enter another number: ");
	fflush(stdout);
	scanf("%d",&num2);

	if(num1==num2){
		printf("You have entered the same number twice");
	}else if(num1>num2){
		printf("The first number you've entered %d is greater than the second one %d",num1,num2);
	}else{
		printf("The first number you've entered %d is less than the second one %d",num1,num2);
	}

	return 0;
}
