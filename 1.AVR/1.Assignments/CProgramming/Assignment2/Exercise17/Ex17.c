#include <stdio.h>

int xorMaxima(int,int);

int main(){

	int num1,num2,result;
	printf("Welcome to Exercise 17 program, Please enter a number: ");
	fflush(stdout);
	scanf("%d %d",&num1,&num2);
	result = xorMaxima(num1,num2);
	printf("%d",result);

	return 0;
}
int xorMaxima(int num1,int num2){
	int maxima = 0;
	for(int i=num1;i<num2;i++){
		for(int j=i;j<num2;j++){
			if((i^j)> maxima){
				maxima = i^j;
			}
		}
	}
	return maxima;
}
