#include <stdio.h>

float calculator(float,float,char);

int main(){

	float num1,num2,result;
	char operator;
	printf("Welcome to Exercise 4 program, please choose an operation: ");
	fflush(stdout);
	scanf("%c",&operator);
	printf("Great. Now please enter a number: ");
	fflush(stdout);
	scanf("%f",&num1);

	printf("Please enter another number: ");
	fflush(stdout);
	scanf("%f",&num2);

	result = calculator(num1,num2,operator);
	printf("result = %f",result);

	return 0;
}
float calculator(float num1,float num2,char operator){
	switch(operator){
	case '+':
		return (num1+num2);
		break;
	case '-':
		return (num1-num2);
		break;
	case '*':
		return (num1*num2);
		break;
	case '/':
		return (num1/num2);
		break;
	default:
		printf("ERROR returning -1\n");
		return -1;
	}

}
