#include <stdio.h>

#define SIZE 10

int main(){
	//int arr[SIZE];
	int arr[SIZE]={1,2,3,4,5,6,7,8,9,10};
	int sum = 0;
	int *ptr;
	printf("Welcome to Exercise 1 program ");
	/*
	 * Printf(",Please enter a number: ");
	for(int i = 0;i<SIZE;i++){
		Printf("Great, Please enter another number: ");
		fflush(stdout);
		scanf("%d",&arr[i]);
	}
	*/
	ptr = arr;
	for(int i = 0;i<SIZE;i++){
		sum+= (*ptr);
		ptr++;
	}
	printf("\nCalculating...\n%d",sum);
	return 0;
}
