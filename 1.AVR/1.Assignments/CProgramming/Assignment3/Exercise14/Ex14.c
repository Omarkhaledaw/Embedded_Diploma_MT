#include <stdio.h>
#include<string.h>

void reverser(char str[]);

int main(){

	char arr[20];
	printf("Welcome to Exercise 14 Program, Please enter a text: ");
	fflush(stdout);
	//scanf("%c",arr);
	gets(arr);

	reverser(arr);

	return 0;
}
void reverser(char str[]){
	int j = strlen(str)-1;
	int i = 0;
	char temp;
	while(i<j){
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;

		i++;
		j--;
	}
	printf("Your string is now '%s'",str);
}
