#include <stdio.h>

void primeRange(int,int);

int main(){

	int num1,num2;
	printf("Welcome to Exercise 7 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);

	printf("Great. Now enter another number but greater than %d: ",num1);
	fflush(stdout);
	scanf("%d",&num2);

	primeRange(num1,num2);

	return 0;
}
void primeRange(int num1,int num2){
	if(num1>num2){
		printf("Error, please try again...");
	}else{
		printf("The prime numbers between %d and %d are: ",num1,num2);
		for(int i = num1;i<num2+1;i++){
			if(i == 0 || i == 1 || (i%2 == 0 && i != 2)){
				printf(" ");
			}else{
				printf("%d ",i);
			}
		}
	}
}
