#include <stdio.h>

int minimumPtrFinder(int arr[]);

int main(){
	int arr[10],result;
	printf("Welcome to Exercise 4 program, ");
	for(int i = 0;i<10;i++){
		printf("Please enter a number: ");
		fflush(stdout);
		scanf("%d",&arr[i]);
	}
	result = minimumPtrFinder(arr);
	printf("Calculating...\n%d",result);

	return 0;
}
int minimumPtrFinder(int arr[]){
	int *ptr= arr;
	for(int i = 0;ptr[i] != '\0';i++){
		if(*ptr > arr[i]){
			*ptr = arr[i];
		}
	}
	return *ptr;
}
