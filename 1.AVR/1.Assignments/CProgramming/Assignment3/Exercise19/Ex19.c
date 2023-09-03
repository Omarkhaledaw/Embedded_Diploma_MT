#include <stdio.h>

int compareStrings(int a[],int b[],int);

int main(){
	int a[]={1,2,3,4,5};
	int b[]={1,2,3,4,5};
	int result;

	printf("Welcome to Exercise 19 Program\n");
	result = compareStrings(a,b,5);
	printf("%d",result);

	return 0;
}
int compareStrings(int a[],int b[],int size){

	for(int i =0;i<size;i++){
		if(a[i] != b[i]){
			return 1;
		}
	}
	return 0;
}
