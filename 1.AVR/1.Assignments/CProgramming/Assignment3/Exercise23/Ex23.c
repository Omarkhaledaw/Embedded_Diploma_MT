#include <stdio.h>

void frequencyCalculator(char str[]);
int g_arr[255]={0};

int main(){
	char str[20];
	printf("Welcome to Exercise 23 program, please enter a text: ");
	fflush(stdout);
	gets(str);
	frequencyCalculator(str);


	return 0;
}
void frequencyCalculator(char str[]){
	int c;
	for(int i = 0;str[i] != '\0';i++){
		c = str[i];
		g_arr[c]++;
	}
	printf("The results are\n");
	for(int i = 0;i<255;i++){
		if(g_arr[i] != 0){
			printf("%c = %d\n",i,g_arr[i]);
		}
	}

}
