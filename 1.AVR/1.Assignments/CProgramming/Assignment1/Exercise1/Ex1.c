#include <stdio.h>

int main(){
	int num1,num2,result;
	printf("Welcome to exercise 1 program/nPlease enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);

	printf("Great please enter another number: ");
	fflush(stdout);
	scanf("%d",&num2);

	result = ((num1+num2)*3)-10;
	printf("((%d+%d)*3)-10 = %d",num1,num2,result);
	return 0;
}
