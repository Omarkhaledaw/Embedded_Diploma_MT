#include <stdio.h>

int checkPowerofThree(int);

int main(){

	int num;
	int result;
	printf("Welcome to Exercise 19 program, Please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	result = checkPowerofThree(num);
	printf("%d",result);

	return 0;
}
int checkPowerofThree(int num){
	if(3==num){
		return 0;
	}else if (num%3 == 0){
		return 0;
	}else{
		return 1;
	}
}
