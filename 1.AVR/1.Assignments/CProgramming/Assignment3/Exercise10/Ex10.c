#include <stdio.h>

void convertToLowercase(char *);

int main(){

	char arr[20];
	printf("Welcome to Exercise 10 Program, Please enter a text: ");
	fflush(stdout);
	gets(arr);
	convertToLowercase(arr);
	printf("After converting\n%s",arr);

	return 0;
}
void convertToLowercase(char arr[]){
	int i = 0;
	while(arr[i] != '\0'){
		if(arr[i] >= 'A' && arr[i] <= 'Z'){
			arr[i] += 32;
		}
		i++;
	}
}
