#include <stdio.h>

void selectionSort(int *,int);

int main(){

	int arr[10]={0,2,3,6,8,1,7,11,10,4};
	printf("Welcome to Exercise 3 Program\n");
	for(int i =0 ;i<10;i++){
		printf("%d, ",arr[i]);
	}
	printf("\nNow After the Selection sorting\n");
	selectionSort(arr,10);
	for(int i =0 ;i<10;i++){
		printf("%d, ",arr[i]);
	}
	return 0;
}
void selectionSort(int *arr,int size){
	int temp,min;
	for(int i =0;i<(size-1);i++){
		min = i;
		for(int j =i+1;j<size;j++){
			if(arr[min]>arr[j]){
				min = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
