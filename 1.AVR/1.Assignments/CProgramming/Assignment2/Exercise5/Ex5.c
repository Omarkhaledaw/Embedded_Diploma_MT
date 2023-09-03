#include <stdio.h>

int checkNum(int);

int main(){

	int num,result;
	printf("Welcome to Exercise 5 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	result = checkNum(num);
	printf("%d",result);

	return 0;
}
int checkNum(int num){
	if(num%2 == 0){
		return 0;
	}else{
		return 1;
	}
}
