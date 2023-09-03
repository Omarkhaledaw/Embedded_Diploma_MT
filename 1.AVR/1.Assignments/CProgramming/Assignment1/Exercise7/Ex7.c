#include <stdio.h>


int main(){
	int num1,num2,num3,smallest;
	printf("Welcome to Exercise 7 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);

	printf("Great! now enter another number: ");
	fflush(stdout);
	scanf("%d",&num2);

	printf("Great! now enter another number: ");
	fflush(stdout);
	scanf("%d",&num3);

	smallest = num1;
	if(smallest>num2){
		smallest = num2;
	}
	if(smallest>num3){
		smallest = num3;
	}
	printf("The smallest number you have entered is %d",smallest);

	return 0;
}
