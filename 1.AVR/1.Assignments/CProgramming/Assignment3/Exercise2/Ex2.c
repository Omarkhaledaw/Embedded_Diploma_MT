#include <stdio.h>

int distinctCharacters(char arr[]);

int main(){

	char arr[20];
	int result;
	printf("Welcome to Exercise 2 Program, Please enter a text: ");
	fflush(stdout);
	scanf("%c",arr);
	/*gets(arr);*/

	result = distinctCharacters(arr);
	printf("%d",result);

	return 0;
}
int distinctCharacters(char arr[]){
	int result = 1;
	int i = 0;
	int j = 0;
	while(arr[i] != '\0'){
		j = i+1;
		while(arr[j] != '\0'){
			if(arr[i] == arr[j]){
				result = 0;
			}
			j++;
		}
		i++;
	}
	return result;
}
