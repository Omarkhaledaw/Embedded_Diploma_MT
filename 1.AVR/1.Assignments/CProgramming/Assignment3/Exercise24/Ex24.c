#include <stdio.h>

int findSecondLargest(int arr[],int size);

int main(){

	int arr[10]={0,1,2,3,4,5,6,7,8,9};
	int result;
	printf("Welcome to Exercise 24 program\n");
	/*
	printf("Enter elements in the array: ");
	for(int i=0; i<10; i++)
	{
		fflush(stdout);
		scanf("%d", &arr[i]);
	}
	*/
	result = findSecondLargest(arr,10);

	printf("Second largest = %d", result);


	return 0;
}
int findSecondLargest(int arr[],int size){
	//int i = 0;
	int max = 0;
	int max2 = 0;

	for(int i = 0;i<size-1;i++){
		if(max < arr[i]){
			max = arr[i];
		}
	}
	for(int i = 0;i<size-1;i++){
		if(arr[i] > max2 && max2 < max){
			max2 = arr[i];
		}
	}
	return max2;
}