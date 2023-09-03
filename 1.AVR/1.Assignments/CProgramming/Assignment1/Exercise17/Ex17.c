#include <stdio.h>


int main(){
	int num,decimal=1;
	printf("Welcome to Ex17 program please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	while(num/10 != 0){
		decimal++;
		num/=10;
	}
	printf("Calculating...\nYour number has %d digits",decimal);
	return 0;
}
