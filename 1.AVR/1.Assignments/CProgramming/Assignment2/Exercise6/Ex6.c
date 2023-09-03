#include <stdio.h>

void convertUppercase(char);

int main(){

	char ch;
	printf("Welcome to Exercise 6 program, please enter a character: ");
	fflush(stdout);
	scanf("%c",&ch);
	convertUppercase(ch);

	return 0;
}
void convertUppercase(char ch){
	printf("\nConverting...\n%c",ch-32);
}
