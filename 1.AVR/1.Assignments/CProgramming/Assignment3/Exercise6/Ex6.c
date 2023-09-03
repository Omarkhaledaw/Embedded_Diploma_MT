#include <stdio.h>

int linearSearch(int arr[],int);

int main(){
	int arr[]={1,2,3,4,4,7};
	int result;
	printf("Welcome to Exercise 6 Program\n");
	result = linearSearch(arr,4);
	printf("%d",result);



	return 0;
}
int linearSearch(int arr[],int num){
	int occ = 0;
	int i = 0;
	while(arr[i] != '\0'){
		if(num == arr[i]){

			if(num == arr[i+1]){
				occ = i+1;
			}else{
				occ = i;
			}
		}
		i++;
	}
	if(occ == 0){
		occ = -1;
	}
	return occ;
}
