#include <stdio.h>


int main(){
	unsigned int grade;
	printf("Welcome to Exercise 9 program please enter your grade: ");
	fflush(stdout);
	scanf("%d",&grade);

	if(grade >= 85 && grade <= 100){
		printf("Excellent!!!");
	}else if(grade >= 75 && grade < 85){
		printf("Very Good!");
	}else if(grade >= 65 && grade < 75){
		printf("Good.");
	}else if(grade >= 50 && grade <65){
		printf("Pass...");
	}else if(grade < 50){
		printf("Fail.");
	}else if(grade > 100 || grade < 0){
		printf("Error please try again later...");
	}
}
