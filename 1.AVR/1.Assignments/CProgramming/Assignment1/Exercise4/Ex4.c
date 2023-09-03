#include <stdio.h>

#define pi 3.14

int main(){

	float radius,circumference;
	printf("Welcome to Exercise 4 program please enter the radius of your circle: ");
	fflush(stdout);
	scanf("%f",&radius);

	circumference = 2 *pi * radius;
	printf("Calculating...\nThe circumference for the radius %f is %f",radius,circumference);
	return 0;
}
