#include <stdio.h>

int linearSearch(int arr[],int);

int main(){
	int arr[]={1,2,2,3,3,3,3,4,4,4,4,3,3,3};
	int result;
	printf("Welcome to Exercise 18 Program\n");
	result = linearSearch(arr,3);
	printf("%d",result);



	return 0;
}
int linearSearch(int arr[],int num){
	int count = 0;
	int consec = 0;
	int i = 0;
	while(arr[i] != '\0'){
		if(num == arr[i]){
			count ++;
		}else{
			if(consec<count){
				consec = count;
			}
			count = 0;
		}
		i++;
	}
	if(count == 0){
		consec = -1;
	}
	return consec;
}
