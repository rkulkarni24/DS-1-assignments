/* 
	Assignment 4 - Singly Linked Lists Operations
	Problem Satement -
	The Department of Computer Engineering is organizing a technical workshop for which students can register in advance. 
	The registration data of students is maintained using a singly linked list. 
	Each registered student is identified by their Registration Number (RegNo) and Name. 
	Write a C program to manage the workshop enrollment system using a singly linked list. 
	Implement the following operations: 
	a) Add a Student 
	b) Remove a Student 
	c) Display the List 
	d) Count Total Participants 
	e) Sort Lists 
	f) Reverse the List  
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{

	char name[30];
	int regno;
	struct node *next;

}Node;

void display(Node *head){
	if (head->next == NULL) {
		printf("Empty Linked List\n");
		return;
	}

	Node *temp = head->next;
	while (temp != NULL) {
		printf("Address : %p\n", temp);
		printf("Student name : %s\n", temp->name);
		printf("Registration No. : %d\n", temp->regno);
		printf("Next Address : %p\n\n", temp->next);
		temp = temp->next;
	}
}

int lengthLL(Node *head){
	int len = 0;
	if (head->next == NULL) {
		return 0;
	}

	Node *temp = head->next;
	while (temp != NULL) {
		len++;
		temp = temp->next;
	}
	return len;
}

void addAtPos(Node *head, char sname[30], int sreg, int pos){
	int len = lengthLL(head);

	if (pos < 1 || pos > len + 1) {
		printf("Invalid Position\n");
		return;
	}

	Node *temp = head;
	for (int i = 1; i < pos; i++) {
		temp = temp->next;
	}

	Node *newnode = (Node *)malloc(sizeof(Node));
	if (newnode == NULL) {
		printf("Memory allocation failed\n");
		return;
	}

	strcpy(newnode->name, sname);
	newnode->regno = sreg;
	newnode->next = temp->next;
	temp->next = newnode;
}

void deleteByData(Node *head, char sname[30]){
	if(head->next == NULL) {
		printf("Empty Linked List\n");
		return;
	}

	Node *prev = head;
	Node *temp = head->next;

	while (temp != NULL && (strcmp(sname, temp->name) != 0)) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		printf("Student name not present\n");
		return;
	}

	prev->next = temp->next;
	temp->next = NULL;
	free(temp);
}

void reverseLL(Node *head){
	if (head->next == NULL) {
		return;
	}

	Node *prev = NULL;
	Node *current = head->next;
	Node *next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	head->next = prev;
}

void sortbydata(Node *head) {
    	if (head->next == NULL) {
        	printf("Empty Linked List\n");
        	return;
    	}
    	Node *curr1 = head->next;
    	while (curr1 != NULL) {
        	Node *curr2 = curr1->next;
        	while (curr2 != NULL) {
            		if (curr1->regno > curr2->regno) {
                
                		int temp_reg = curr1->regno;
                		curr1->regno = curr2->regno;
                		curr2->regno = temp_reg;

               			char temp_name[30];
                		strcpy(temp_name, curr1->name);
                		strcpy(curr1->name, curr2->name);
                		strcpy(curr2->name, temp_name);
            		}
            		curr2 = curr2->next;
        	}
        	curr1 = curr1->next;
    	}
}

void sortbynode(Node *head) {
	int len = lengthLL(head);
    	if (head->next == NULL) {
        	return;
    	}

    	for (int p = 0; p < len - 1; p++) {
        	Node *prev = head;
        	Node *curr1 = head->next;

        	while (curr1 != NULL && curr1->next != NULL) {
            		Node *curr2 = curr1->next;

            		if (curr1->regno > curr2->regno) {
                
                		curr1->next = curr2->next;
                		curr2->next = curr1;
                		prev->next = curr2;
						prev = curr2;
            		} 
            		else {
                
                		prev = curr1;
                		curr1 = curr1->next;
            		}
        	}
    	}
}


int main(){

	Node *head;
	
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	
	int len;
	
	char tname[30];
	char del[30];
	int regnum;
	int pos;
	
	int choice;
	
	do{
	
		printf("\nEnter 1 to display LL\nEnter 2 to get length of LL\nEnter 3 to add data by position\nEnter 4 to remove by student name\nEnter 5 to reverse the linked list\nEnter 6 to sort by registration number(sorting only the data)\nEnter 7 to sort node by registration number\n");
		printf("Enter your choice : ");
		scanf("%d", &choice);
		
		switch(choice){
		
			case 1 :
				
				printf("Linked List : \n");
				display(head);
				break;
				
			case 2:
				len = lengthLL(head);
				if(len == 0){
					printf("Empty Linked List\n");
				}
				else{
					printf("Length of Linked List : %d\n", len);
				}
				break;
				
			case 3 : 
				
				printf("Enter Student name : ");
				scanf(" %[^\n]",tname);
				printf("Enter Registration No. : ");
				scanf("%d",&regnum);
				printf("Enter position : ");
				scanf("%d",&pos);
				
				addAtPos(head, tname, regnum, pos);
				
				break;
				
			case 4 : 
			
				printf("Enter student name to delete : ");
				scanf(" %[^\n]",del);
				
				deleteByData(head, del);
				
				break;

			case 5 :
				reverseLL(head);
				display(head);
				break;
				
			case 6 :
				sortbydata(head);
				display(head);
				break;
				
			case 7 :
				sortbynode(head);
				display(head);
				break;
				
			default :
				printf("Invalid choice\n");
				break;
				
		}
		
	} while (choice <= 7 && choice != 0);
	
	return 0;
				
}
