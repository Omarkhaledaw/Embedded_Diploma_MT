#include <stdio.h>
#include <math.h>

int powerOfTwo(float num);

int main(){

	float num;
	int result;
	printf("Welcome to Exercise 11 program, Please enter a number: ");
	fflush(stdout);
	scanf("%f",&num);
	result = powerOfTwo(num);
	printf("%d",result);

	return 0;
}
int powerOfTwo(float num){
	int result;
	float temp;
	temp = sqrt(num);
	/*
	if(1 == num){
		result = 1;
	}else if (0 ==num){
		result = 0;
	}else if(0 == temp%2.0){
		result = 1;
	}else{
		result = 0;
	}
	*/
	return result;
}
