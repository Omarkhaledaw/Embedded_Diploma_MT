#include <stdio.h>

void bubbleSort(int *,int);

int main(){

	int arr[10]={0,2,3,6,8,1,7,11,10,4};
	printf("Welcome to Exercise 3 Program\n");
	for(int i =0 ;i<10;i++){
		printf("%d, ",arr[i]);
	}
	printf("\nNow After the Bubble sorting\n");
	bubbleSort(arr,10);
	for(int i =0 ;i<10;i++){
		printf("%d, ",arr[i]);
	}
	return 0;
}
void bubbleSort(int *arr,int size){
	int temp;
	for(int i =0;i<(size-1);i++){
		for(int j =0;j<(size-1);j++){
			if(arr[j]>arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
