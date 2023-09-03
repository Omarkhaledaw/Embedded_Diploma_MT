#include <stdio.h>


int main(){
	unsigned int num;
	printf("Welcome to Exercise 13 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);

	if((num%2 == 0 && num != 2) || num == 1 || num == 0){
		printf("The number you have entered is not a prime number.");
	}else{
		printf("The number you have entered is a prime number.");
	}
	return 0;
}
