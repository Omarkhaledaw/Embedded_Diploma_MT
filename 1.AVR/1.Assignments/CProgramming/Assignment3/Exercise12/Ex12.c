#include <stdio.h>
#include<string.h>

void lengthCalculator(char str[]);

int main(){

	char arr[20];
	printf("Welcome to Exercise 12 Program, Please enter a text: ");
	fflush(stdout);
	//scanf("%c",arr);
	gets(arr);

	lengthCalculator(arr);

	return 0;
}
void lengthCalculator(char str[]){
	int count = 0;
	int i = 0;
	while(str[i] != '\0'){
		count++;
		i++;
	}
	printf("The length of string '%s' is %d",str,count);
}
