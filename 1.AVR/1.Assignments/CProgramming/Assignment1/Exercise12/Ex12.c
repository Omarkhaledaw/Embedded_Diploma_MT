#include <stdio.h>

int factorial(int);
int main(){
	unsigned int num,result;
	printf("Welcome to Exercise 12 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);

	result = factorial(num);
	printf("Calculating...\nThe factorial of %d is %d",num,result);
	return 0;
}
int factorial(int n){
	if(n==0 || n==1){
		return 1;
	}else{
		return n*factorial(n-1);
	}
}
