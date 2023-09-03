#include <stdio.h>

void checkMultiple(int,int);

int main(){

	int num1,num2;
	printf("Welcome to Exercise 7 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);

	printf("Great. Now enter another number: ");
	fflush(stdout);
	scanf("%d",&num2);

	checkMultiple(num1,num2);

	return 0;
}
void checkMultiple(int num1,int num2){
	if(num1%num2 == 0){
		printf("The number %d is multiple of the number %d",num2,num1);
	}else{
		printf("The number %d is NOT multiple of the number %d",num2,num1);
	}
}
