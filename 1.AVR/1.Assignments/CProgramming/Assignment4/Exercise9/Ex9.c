#include <stdio.h>

void changeByPtr(char*);
char result[4];


int main(){
	char str[20];
	printf("Welcome to Exercise 9 program, Please enter a text: ");
	fflush(stdout);
	scanf("%s",str);
	changeByPtr(str);
	printf("%s",result);

	return 0;
}
void changeByPtr(char*word){
	char* ptr = word;
	for(int i = 0;word[i] != '\0';i++){
		ptr++;
	}
	result[0] = *(--ptr);
	result[1] = ' ';
	result[2] = *(--ptr);
	result[3] = '\0';
}
