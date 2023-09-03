#include <stdio.h>


int main(){
	int arr[]={1,2,3,4,5,6,7,8,9,10};
	int *ptr = arr;
	int count = 0;
	printf("Welcome to Exercise 2 program ");
	for(int i = 0;*ptr != '\0';i++){
		count++;
		ptr++;
	}
	printf("\nCalculating...\n%d",count);
	return 0;
}
