#include <stdio.h>

int findTheOddOne(int*,int);

int main(){
	int result;
	int arr[15]={1,2,3,1,2,3,1,1,1,1,3,3,3};
	printf("Welcome to Exercise 12 program\nCalculating...");
	result = findTheOddOne(arr,15);
	printf("%d",result);

	return 0;
}
int findTheOddOne(int *arr,int size){
	int count = 0,odd;

	for(int i = 0;i<size-1;i++){
		for(int j = 0;j<size-1;j++){
			if(arr[i] == arr[j]){
				count++;
			}
		}
		if(count%2 == 0){
			count = 0;
		}else{
			odd=arr[i];
			break;
		}
	}
	return odd;
}
