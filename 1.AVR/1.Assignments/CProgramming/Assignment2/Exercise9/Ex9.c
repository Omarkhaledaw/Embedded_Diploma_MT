#include <stdio.h>

void swap(int*,int*);

int main(){

	int num1,num2;
	printf("Welcome to Exercise 9 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);

	printf("Great. Now enter another number: ");
	fflush(stdout);
	scanf("%d",&num2);

	printf("The first number is: %d\nThe second number is: %d",num1,num2);
	swap(&num1,&num2);

	printf("\nSwapping...\nThe first number is: %d\nThe second number is: %d",num1,num2);

	return 0;
}
void swap(int *num1,int *num2){
	int temp;
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
