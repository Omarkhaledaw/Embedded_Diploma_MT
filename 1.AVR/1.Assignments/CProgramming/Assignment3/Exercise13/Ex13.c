#include <stdio.h>

void nonAlphabeticRemover(char str[]);

int main(){

	char arr[20];
	printf("Welcome to Exercise 13 Program, Please enter a text: ");
	fflush(stdout);
	//scanf("%c",arr);
	gets(arr);

	nonAlphabeticRemover(arr);

	printf("The character after removing non alphabetic letters: %s",arr);
	return 0;
}
void nonAlphabeticRemover(char str[]){
	int i = 0;
	while(str[i] != '\0'){
		if(!((str[i] >= 'A' && str[i] <= 'Z')||(str[i] >= 'a' && str[i] <= 'z'))){
			str[i] = ' ';
		}
		i++;
	}
}
