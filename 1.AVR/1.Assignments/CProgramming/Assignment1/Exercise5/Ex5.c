#include <stdio.h>

int main(){
	char letter;
	printf("Welcome to exercise 5 program\nPlease enter a character: ");
	fflush(stdout);
	scanf("%c",&letter);

	printf("The ASCI value of the letter %c is %d",letter,letter);
	return 0;
}
