#include <stdio.h>

int main(){
	float num1,num2,result;
	char operator;
	printf("Welcome to Exercise 10 program please select the operation you want to make: ");
	fflush(stdout);
	scanf("%c",&operator);
	if(operator == '-' || operator == '+' || operator == '/' || operator == '*' ){

		printf("Great you choose %c\nNow please enter a number: ");
		fflush(stdout);
		scanf("%f",&num1);

		printf("Please enter another number: ");
		fflush(stdout);
		scanf("%f",&num2);

		if(operator == '+'){
			result = num1+num2;
		}else if(operator == '-'){
			result = num1-num2;
		}else if(operator == '/'){
			result = num1/num2;
		}else{
			result = num1*num2;
		}
		printf("Calculating...\n %f %c %f = %f",num1,operator,num2,result);
	}else{
		printf("Error please try again later");
	}
	return 0;
}
