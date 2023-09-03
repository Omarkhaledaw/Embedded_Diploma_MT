#include <stdio.h>

void cube(int);

int main(){

	int num;
	printf("Welcome to Exercise 1 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	cube(num);

	return 0;
}
void cube(int num){
	int result;
	result = num*num*num;
	printf("%d",result);
}
