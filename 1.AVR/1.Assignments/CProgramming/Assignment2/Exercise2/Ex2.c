#include <stdio.h>

void checkAlphabet(char);

int main(){

	char ch;
	printf("Welcome to Exercise 2 program, please enter a character: ");
	fflush(stdout);
	scanf("%c",&ch);
	checkAlphabet(ch);

	return 0;
}
void checkAlphabet(char ch){
	if((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')){
		printf("The character you have entered is from the Alphabets");
	}else{
		printf("The character you have entered is NOT from the Alphabets");
	}
}
