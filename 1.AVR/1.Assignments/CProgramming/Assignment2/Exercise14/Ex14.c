#include <stdio.h>

int fibonacci(int num);

int main(){

	int num,result;
	printf("Welcome to Exercise 14 program, Please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	result = fibonacci(num);
	printf("Calculating...\n%d",result);

	return 0;
}
int fibonacci(int num){

	if(0 == num){
		return 0;
	}else if(1 == num){
		return 1;
	}else{
		return fibonacci(num-1)+fibonacci(num-2);
	}
}
