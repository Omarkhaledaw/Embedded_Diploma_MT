#include <stdio.h>

int linearSearch(int arr[],int);

int main(){
	int arr[]={1,2,3,4,4,4};
	int result;
	printf("Welcome to Exercise 5 Program\n");
	result = linearSearch(arr,4);
	printf("%d",result);



	return 0;
}
int linearSearch(int arr[],int num){
	int count = 0;
	int i = 0;
	while(arr[i] != '\0'){
		if(num == arr[i]){
			count++;
		}
		i++;
	}
	if(count == 0){
		count = -1;
	}
	return count;
}
