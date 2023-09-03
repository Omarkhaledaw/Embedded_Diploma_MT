#include <stdio.h>

void swappingPtr2Ptr(int**,int**);


int main(){
	int num1,num2;

	printf("Welcome to Exercise 7 program, please enter a number: ");
	fflush(stdout);
	scanf("%d",&num1);
	printf("Great, now enter another number: ");
	fflush(stdout);
	scanf("%d",&num2);

	int *ptr1 = &num1;
	int *ptr2 = &num2;

	printf("Before swapping\nNum 1 = %d\nNum 2 = %d",*ptr1,*ptr2);
	swappingPtr2Ptr(&ptr1,&ptr2);
	printf("\nAfter swapping\nNum 1 = %d\nNum 2 = %d",*ptr1,*ptr2);


	return 0;
}
void swappingPtr2Ptr(int** ptr1,int** ptr2){
	int *temp;
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;

}
