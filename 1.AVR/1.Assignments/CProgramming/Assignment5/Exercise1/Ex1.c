#include <stdio.h>

struct Student{
	char name[10];
	int age;
	int role;
}num1;


int main(){
	char name[10];
	int age,role;

	printf("Welcome to Exercise 1 program, please enter a name: ");
	fflush(stdout);
	gets(num1.name);

	printf("Great, please enter the age: ");
	fflush(stdout);
	scanf("%d",&num1.age);

	printf("Great, please enter the role: ");
	fflush(stdout);
	scanf("%d",&num1.role);



	printf("\nThe id for student number 1\nName: %s\nAge: %d\nRole: %d",num1.name,num1.age,num1.role);
	return 0;
}
