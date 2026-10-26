/*
	Assignment 8 - Linear Queue
	Problem Statement - 
	In a networked environment, a shared printer receives multiple print requests from users throughout the day. 
	To handle these requests efficiently and ensure optimal memory usage, the system implements a linear queue to manage the 
	list of print jobs. 
	Each print job is identified by a Job ID and a Document Title. 
	The print jobs are processed in the order they are received (FIFO order), and memory is reused as jobs are completed 	
*/

#include <stdio.h>
#include <string.h>

typedef struct print_job{
 	int job_id;
 	char job_title[20];
}Job;
 
Job queue[20];
 
int front = -1;
int rear = -1;
 
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
	if(rear == 19){
		return 1;
	}
	else{
		return 0;
	}
}

void enque(Job job){
	
	rear++;
		
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

	front++;
		
	Job save = queue[front];

	return save;
	
}

void display(){

	if(front == rear){
		printf("Queue is Empty.\n");
	}
	else
	{
		printf("Job queue is as follows :\n");
		for(int i = front; i<=rear; i++)
		{
			printf("Job id : ");
			printf("%d",queue[i].job_id);
			printf("\nJob title : ");
			printf("%s",queue[i].job_title);
			printf("\n");
		}
	}
	printf("\n");
	
}
