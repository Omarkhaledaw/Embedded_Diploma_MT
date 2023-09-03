#include <stdio.h>

int main(){
	int num1 = 0xFFFFAAAA;
	int num2 = 0;

	short *ptr1 = (short*)&num1;
	short *ptr2 = (short*)&num2;

	printf("The value before swapping %X",num2);

	ptr2[0]=ptr1[1];
	ptr2[1]=ptr1[0];

	printf("\nThe value after swapping %X",num2);



	return 0;
}
