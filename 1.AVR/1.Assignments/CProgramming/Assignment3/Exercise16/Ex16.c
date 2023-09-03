#include <stdio.h>
#include<string.h>

void reverser(int arr[],int);


int main(){

	int arr[6]={0,1,2,3,4,5};
	printf("Welcome to Exercise 1 Program\n");

	for(int i =0;i<6;i++){
		printf("%d ",arr[i]);
	}
	reverser(arr,6);
	printf("\nAfter reversing\n");
	for(int i =0;i<6;i++){
		printf("%d ",arr[i]);
	}
	return 0;
}
void reverser(int arr[],int size){
	int i=0;
	int temp;
	while(i<(size/2)){
		temp = arr[i];
		arr[i] = arr[size-1-i];
		arr[size-1-i] = temp;
		i++;
	}
}
