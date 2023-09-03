#include <stdio.h>

struct Student{
	char name[20];
	int id;
	int grade;
}class[10];
void storeInfo(struct Student *);
void displayInfo(struct Student *);

int main(){

	printf("Welcome to Exercise 5 program\n");

	storeInfo(class);
	displayInfo(class);

	return 0;
}
void storeInfo(struct Student *num){
	printf("Please enter the students info\n");
	for(int i =1;i<11;i++){
		printf("Name: ");
		fflush(stdout);
		scanf("%s",num->name);
		printf("id: ");
		fflush(stdout);
		scanf("%d",&num->id);
		printf("Grade: ");
		fflush(stdout);
		scanf("%d",&num->grade);
		num++;
	}
}
void displayInfo(struct Student *num){
	printf("Displaying students info\n");
	for(int i =1;i<11;i++){
		printf("Student no.%d\nName: %s\nid: %d\nGrade: %d",i,num->name,num->id,num->grade);
		num++;
	}
}
