#include <stdio.h>

void AllandMax(int*,int);


int main(){
	int arr[10]={0,1,2,3,4,5,6,7,8,9};
	printf("Welcome to Exercise 6 program\n");
	AllandMax(arr,10);


	return 0;
}
void AllandMax(int* ptr,int size){
	int max = 0;
	for(int i = 0;i<size;i++){
		printf("%d ",ptr[i]);
		if(max < ptr[i]){
			max = ptr[i];
		}
	}
	printf("\nMaximum number = %d",max);
}
