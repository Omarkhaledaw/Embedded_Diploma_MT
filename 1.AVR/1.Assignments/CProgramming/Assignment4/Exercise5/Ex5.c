#include <stdio.h>

void copywithptr(int*,int*,int);

int main(){
	int arr1[10]={0};
	int arr2[10]={0,1,2,3,4,5,6,7,8,9};
	printf("Welcome to Exercise 5 program\n");

	for(int i =0;i<10;i++){
		printf("%d ",arr1[i]);
	}
	printf("\n");
	for(int i =0;i<10;i++){
		printf("%d ",arr2[i]);
	}
	printf("\n");
	copywithptr(arr1,arr2,10);
	for(int i =0;i<10;i++){
		printf("%d ",arr1[i]);
	}
	printf("\n");
	for(int i =0;i<10;i++){
		printf("%d ",arr2[i]);
	}
	printf("\n");
	return 0;
}
void copywithptr(int *ptr1,int *ptr2,int size){
	for(int i = 0;i<size;i++){
		*ptr1=*ptr2;
		ptr1++;
		ptr2++;
	}
}
