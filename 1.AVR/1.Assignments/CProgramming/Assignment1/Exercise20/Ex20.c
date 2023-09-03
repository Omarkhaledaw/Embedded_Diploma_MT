#include <stdio.h>


int main(){
	int num;
	printf("Welcome to Ex20 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	for(int i = 0;i<num;i++){
		for(int j = i;j<(num/2)-1;j++){
			printf(" ");
		}
		for(int k =num-i;k<num+1;k++){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
