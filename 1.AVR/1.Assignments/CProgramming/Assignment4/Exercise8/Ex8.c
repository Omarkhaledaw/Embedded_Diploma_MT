#include <stdio.h>

void swapStrPtr(int,int,int*,int*);

int main(){

	int arr1[10]={0,1,2,3,4,5,6,7,8,9};
	int arr2[10]={10,20,30,40,50,60,70,80,90,100};

	printf("Welcome to Exercise 8 program\nBefore swapping\n");

	for(int i = 0;i<10;i++){
		printf("%d ",arr1[i]);
	}
	printf("\n");
	for(int i = 0;i<10;i++){
		printf("%d ",arr2[i]);
	}
	printf("\nAfter swapping\n");

	swapStrPtr(10,10,arr1,arr2);

	for(int i = 0;i<10;i++){
		printf("%d ",arr1[i]);
	}
	printf("\n");
	for(int i = 0;i<10;i++){
		printf("%d ",arr2[i]);
	}

	return 0;
}
void swapStrPtr(int size1,int size2, int* ptr1,int* ptr2){
	if(size1 != size2){
		printf("ERROR");
	}else{
		int temp;
		for(int i = 0;i<size1;i++){
			temp = *ptr1;
			*ptr1 = *ptr2;
			*ptr2 = temp;

			ptr1++;
			ptr2++;
		}
	}
}
