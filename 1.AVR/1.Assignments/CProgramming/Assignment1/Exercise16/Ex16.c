#include <stdio.h>


int main(){
	int num,reserved=0,temp;
	printf("Welcome to Ex16 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	while(num/100 != 0){
		temp = num%10;
		reserved = (reserved*10) + temp;
		num/=10;
	}
	printf("%d",reserved);
	return 0;
}
