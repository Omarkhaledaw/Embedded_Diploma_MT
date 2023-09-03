#include <stdio.h>


int main(){

	int num;
	printf("Welcome to Ex18 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);

	for(int i =0;i<num;i++){
		for(int j =num-i;j<num+1;j++){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
