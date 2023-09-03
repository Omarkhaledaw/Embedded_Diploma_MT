#include <stdio.h>

struct complex{
	int real;
	int imaginary;
}num1,num2;

void complexSummation(struct complex,struct complex);

int main(){
	printf("Welcome to Exercise 3 program, please enter the two complex numbers\nReal part: ");
	fflush(stdout);
	scanf("%d",&num1.real);
	printf("Imaginary part: ");
	fflush(stdout);
	scanf("%d",&num1.imaginary);

	printf("Great, now enter the second number\nReal part: ");
	fflush(stdout);
	scanf("%d",&num2.real);
	printf("Imaginary part: ");
	fflush(stdout);
	scanf("%d",&num2.imaginary);
	complexSummation(num1,num2);

	return 0;
}
void complexSummation(struct complex num1,struct complex num2){
	int real,imaginary;
	real=num1.real+num2.real;
	imaginary=num1.imaginary+num2.imaginary;

	printf("Calculating...\n%d+%d i",real,imaginary);
}
