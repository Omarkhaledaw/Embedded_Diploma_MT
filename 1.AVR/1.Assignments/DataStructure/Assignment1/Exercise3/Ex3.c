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
int sizeOfList();
void printList();
void whatIsTheMiddle();
void whatIsThePosition(int);

int main(){

	int size;

	insertAtLast(11);
	insertAtLast(3);
	insertAtLast(10);
	insertAtLast(15);
	insertAtLast(50);
	insertAtLast(23);
	insertAtLast(5);
	insertAtLast(60);

	printList();
	size = sizeOfList();
	printf("%d",size);
	whatIsThePosition(5);

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
int sizeOfList(){

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
	return size;
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
		printf("The list\n");
		while(current->next != NULL){
			printf("%d ",current->data);
			current = current->next;
		}
		printf("%d ",current->data);
	}
}
void whatIsTheMiddle(){
	int size = sizeOfList();
	current = head;
	if(size == 1){
		printf("%d",current->data);
	}else{
		int pos=0,middle=size/2;
		while(pos<middle){
			pos++;
			previous = current;
			current = current->next;
		}
		printf("\nThe middle node data is %d",current->data);
	}
}
void whatIsThePosition(int position){

	current = head;
	int pos=1;
	while(pos<position){
		pos++;
		previous = current;
		current = current->next;
	}
	printf("\nThe %d th node data is %d",position,current->data);

}
