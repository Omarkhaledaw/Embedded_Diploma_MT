#include <stdio.h>

int summation(int,int*);

int main(){
	int arr[4];
	int result;
	printf("Welcome to Exercise 1 Program, Please enter a number: ");
	fflush(stdout);
	scanf("%d",&arr[0]);
	for(int i =1;i<4;i++){
		printf("Great!. Please enter another number: ");
		fflush(stdout);
		scanf("%d",&arr[i]);
	}
	result = summation(4,arr);
	printf("Calculating...\nThe sum of your array is %d",result);

	return 0;
}
int summation(int number_size,int* numbers){
	int sum = 0;
	for(int i =0;i<number_size;i++){
		sum += numbers[i];
	}
	return sum;
}
