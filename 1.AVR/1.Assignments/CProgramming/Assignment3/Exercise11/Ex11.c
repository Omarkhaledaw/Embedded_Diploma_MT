#include <stdio.h>

void freqCalculator(char str[],char ch);

int main(){

	char arr[20];
	char ch;
	printf("Welcome to Exercise 11 Program, Please enter a text: ");
	fflush(stdout);
	//scanf("%c",arr);
	gets(arr);
	printf("Great, Please enter the character you want to search for: ");
	fflush(stdout);
	scanf("%c",&ch);

	freqCalculator(arr,ch);

	return 0;
}
void freqCalculator(char str[],char ch){
	int count = 0;
	int freq = 0;
	int i = 0;
	while(str[i] != '\0'){
		count++;
		if(ch == str[i]){
			freq++;
		}
		i++;
	}
	printf("The character '%c' has appeared %d times",ch,freq);
}
