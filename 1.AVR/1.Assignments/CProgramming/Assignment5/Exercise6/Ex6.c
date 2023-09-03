#include <stdio.h>

union Family_name{

	char first_name[30];
	char last_name[30];
};


int main(){
	union Family_name omar;
	printf("Welcome to Exercise 6 program please enter your first name: ");
	fflush(stdout);
	scanf("%s",omar.first_name);

	printf("%s %d",omar.last_name,sizeof(omar));


	return 0;
}
