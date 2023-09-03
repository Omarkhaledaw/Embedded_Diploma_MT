#include <stdio.h>

void heatingTimeCalculator(float);

int main(){


	float temp;
	printf("Welcome to Exercise 12 program, Please enter the temperature: ");
	fflush(stdout);
	scanf("%f",&temp);
	heatingTimeCalculator(temp);

	return 0;
}
void heatingTimeCalculator(float temp){

	int heatingTime;

	if((temp >= 0.0)&&(temp <= 30.0)){
		heatingTime = 7;
		printf("The required heating time is %d",heatingTime);
	}else if((temp >= 30.0)&&(temp <= 60.0)){
		heatingTime = 5;
		printf("The required heating time is %d",heatingTime);
	}else if((temp >= 60.0)&&(temp <= 90.0)){
		heatingTime = 3;
		printf("The required heating time is %d",heatingTime);
	}else if((temp >= 90.0)&&(temp <= 100.0)){
		heatingTime = 1;
		printf("The required heating time is %d",heatingTime);
	}else{
		heatingTime = 0;
		printf("The required heating time is %d",heatingTime);
	}
}
