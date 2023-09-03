#include <stdio.h>

int main(){
	float celsius,fahrenheit;
	printf("Welcome to Ex3 program please enter temperature in celsius: ");
	fflush(stdout);
	scanf("%f",&celsius);
	fahrenheit = ((celsius * 9)/5)+32;

	printf("Converting...\nThe temperature in fahrenheit is %f ",fahrenheit);
	return 0;
}
