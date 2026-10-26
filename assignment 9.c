/* 
	Assignment 9 - Circular Queue 
	Problem Statement - 
	Write a C program to simulate a Printer Queue Manager using a circular queue implemented
	with an array. 
	a) Add a Print Job (Enqueue) 
	b) Process a Print Job (Dequeue) 
	c) Display All Pending Print Jobs
*/

#include <stdio.h>
#include <string.h>

typedef struct print_job
{
 	int job_id;
 	char job_title[20];
}Job;
 
Job queue[20];
 
int front = 0;
int rear = 0;
 
int isFull();
void enque(Job job);
int isEmpty();
Job deque();
void display();

int main()
{
	
	Job job, del;
	int choice;
	
	do{
		printf("\nEnter 1 to add to queue\nEnter 2 to remove from queue\nEnter 3 to display queue\n");
		printf("Enter your choice : ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				if(isFull() == 1){
					printf("Queue is FULL.\n");
				}
				else{
					printf("Enter job details\n");
					printf("Enter job id : ");
					scanf("%d",&job.job_id);
					printf("Enter job title :");
					scanf(" %19[^\n]",job.job_title);
				
					enque(job);

					printf("Job has been queued.\n");
				}
				
				break;
				
			case 2:
			
				if(isEmpty() == 1){
					printf("Queue is EMPTY.\n");
				}
				else{
					del = deque();
					printf("Deleted Job is job id -> %d and job title -> %s.\n", del.job_id, del.job_title);
	
				}	
				
				break;
				
			case 3:
			 	
			 	display();
			 	break;
			 	
			default :
				printf("Invalid choice\n");
			 	break;
			 	
		}
	}while(choice <= 3 && choice != 0);
	
	return 0;
	
}

int isFull(){
	if((rear + 1)%20 == front){
		return 1;
	}
	else{
		return 0;
	}
}

void enque(Job job){
	
	rear = (rear+1)%20 ;
		
	queue[rear].job_id = job.job_id;
		
	strcpy(queue[rear].job_title, job.job_title);
}

int isEmpty(){
	if(front == rear){
		return 1;
	}
	else{
		return 0;
	}
}

Job deque(){

	front = (front+1)%20;
		
	Job save = queue[front];

	return save;
}

void display(){

	if(isEmpty() == 1){
		printf("Queue is EMPTY.\n");
		return;
	}

	int i = (front + 1)%20;
	while (1)
	{
		printf("Job id : ");
		printf("%d",queue[i].job_id);
		printf("\nJob title : ");
		printf("%s",queue[i].job_title);
		printf("\n");

		if(i == rear) break;

		i = (i + 1)%20;
	}
	
}
