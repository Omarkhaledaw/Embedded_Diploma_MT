#include <stdio.h>


int main(){
	int num,power;
	printf("Welcome to Ex15 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);

	printf("Great! now enter the power number: ");
	fflush(stdout);
	scanf("%d",&power);

	for(int i =0;i<(power-1);i++){
		num*=num;
	}
	printf("%d",num);
	return 0;
}
