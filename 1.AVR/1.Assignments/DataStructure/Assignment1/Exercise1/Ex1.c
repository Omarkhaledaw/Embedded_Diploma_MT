#include <stdio.h>

struct Node {
	int data;
	struct Node *next;
};

struct Node *head = NULL;
struct Node *current = NULL;
struct Node *previous = NULL;

void insertBetween(int,int);
void insertAtLast(int);
void sizeOfList();
void printList();

int main(){

	insertAtLast(11);
	insertAtLast(3);
	insertAtLast(10);
	insertAtLast(50);
	insertAtLast(23);
	insertAtLast(5);
	insertAtLast(60);

	printList();
	sizeOfList();

	insertBetween(15,3);

	printList();
	sizeOfList();

	return 0;
}
void insertAtLast(int data){

	struct Node *link = (struct Node*)malloc(sizeof(struct Node));

	link->data = data;
	link->next = NULL;

	if(head == NULL){
		head = link;
		return;
	}
	current = head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = link;
}
void sizeOfList(){

	int size = 0;
	if(head == NULL){
		size = -1;
	}else{
		size = 1;
		current = head;
		while(current ->next != NULL){
			size++;
			current = current->next;
		}
	}
	printf("\nSize of the list = %d",size);
}
void insertBetween(int data,int position){

	struct Node *link = (struct Node*)malloc(sizeof(struct Node));
	link->data = data;
	link->next = NULL;

	if(head == NULL){
		head = link;
	}else{
		int num =0;
		current = head;
		while(num<position){
			num++;
			previous = current;
			current = current->next;
		}
		link->next = current;
		previous->next = link;
	}
}
void printList(){
	if(head == NULL){
		printf("EMPTY LIST!!!");
	}else{
		current = head;
		printf("\nThe list\n");
		while(current->next != NULL){
			printf("%d ",current->data);
			current = current->next;
		}
		printf("%d ",current->data);
	}
}
