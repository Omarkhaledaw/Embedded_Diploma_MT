#include <stdio.h>

int * Swap (int,int *,int,int *);


int main(){
	int a [6]={0,1,2,3,4,5};
	int b [5]={6,7,8,9,10};


	printf("Array1 before the Swap : ");
	for(int i=0;i<5;i++){
		printf("%d ",a[i]);
	}
	printf("\n");

	printf("Array2 before the Swap : ");
	for(int i=0;i<5;i++){
		printf("%d ",b[i]);
	}

	Swap(6,a,5,b);
	printf("\n");
	printf("\n");

	printf("Array1 after the Swap : ");
	for(int i=0;i<5;i++){
		printf("%d ",a[i]);
	}
	printf("\n");

	printf("Array2 after the Swap : ");
	for(int i=0;i<5;i++)
	{
		printf("%d ",b[i]);
	}
	printf("\n");

	return 0;
}
int * Swap (int a_size,int *a,int b_size,int *b){
	int temp;
	for(int i = 0;i<b_size;i++){
		temp = a[i];
		a[i] = b[i];
		b[i] = temp;
	}
	return a;
}
