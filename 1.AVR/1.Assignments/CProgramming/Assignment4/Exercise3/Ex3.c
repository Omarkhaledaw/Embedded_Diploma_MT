#include <stdio.h>

#define SIZE 10

int main(){
	int arr[SIZE];
	int *ptr;
	printf("Welcome to Exercise 3 program, ");
	for(int i = 0;i<SIZE;i++){
		printf("Please enter a number: ");
		fflush(stdout);
		scanf("%d",&arr[i]);
	}
	ptr = &arr[SIZE-1];
	for(int i = SIZE;i>=0;i--){
		printf("%d ",*ptr);
		ptr--;
	}
	return 0;
}
