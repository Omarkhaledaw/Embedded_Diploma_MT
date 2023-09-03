#include <stdio.h>
#include<string.h>

void concatManual(char str1[],char str2[],char str[]);


int main(){
	char arr[200];
	char arr1[20];
	char arr2[20];
	printf("Welcome to Exercise 15 Program, Please enter a text: ");
	fflush(stdout);
	gets(arr1);
	printf("Great, Please enter another text: ");
	fflush(stdout);
	gets(arr2);

	concatManual(arr1,arr2,arr);
	printf("%s",arr);

	return 0;
}
void concatManual(char str1[],char str2[],char str[]){
	int i=0,j=0;
	while(str1[i] != '\0'){
		str[i] = str1[i];
		i++;
	}
	//i++;
	while(str2[j] != '\0'){
		str[i] = str2[j];
		j++;
		i++;
	}
	//i++;
	str[i] = '\0';
}
