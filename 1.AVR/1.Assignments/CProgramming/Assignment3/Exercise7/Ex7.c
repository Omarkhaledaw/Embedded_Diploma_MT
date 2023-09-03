#include <stdio.h>

int arithmeticSeries(int);

int main(){

	int num,result;
	printf("Welcome to Exercise 7 Program, Please enter a number: ");
	fflush(stdout);
	scanf("%d",&num);
	result = arithmeticSeries(num);
	printf("The %d term of arithmetic series %d",num,result);

	return 0;
}
int arithmeticSeries(int num){
	int count = 1;
	for(int i = 0;i<num;i++){
		count+=2;
	}
	return count;
}
