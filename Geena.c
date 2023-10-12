#include <stdio.h>
#include <stdlib.h>
# define MAX 10

struct node
{
	int data;
	struct node *next;
};

typedef struct node queue;

queue *front=NULL;
queue *rear=NULL;
int token_num=11;

void enqueue()
{
	queue *t = (queue *)malloc(sizeof(queue));
	t->data=token_num;
	t->next=NULL;
	if(front == NULL)
	{
		front = t;
		rear = t;
	}
	else
	{
		rear->next = t;
		rear = t;
	}
}

void dequeue()
{
	if(front==NULL)
		printf("Queue Empty\n");
	else
	{
		printf("\nNow serving customer number: %i",front->data);
		printf("\n\n");
		front = front->next;
		if(front == NULL)
			rear=NULL;
	}
}

void display()
{
	if(front==NULL)
		printf("Empty Queue\n");
	else
	{
		queue *t=front;
		while(t != NULL)
		{
			printf("%d\t",t->data);
			t=t->next;
		}
	}
}

void generate_customer_num() //generate a number and add to the queue
{
	token_num= token_num + 1;
	printf("\nYour customer token number is : %i",token_num);
	printf("\n\n");
	enqueue();
//	enqueue(Queue,index_num);
}


int main()
{
	int choice_admin, choice_customer, st;
	
	start:
		
		printf("*****WELCOME TO HOSPITAL*****\n\n");
		printf("1. Press 1 to get customer token\n\n2. Press 2 for go to admin panel\n\n3. Press 3 to Logoff\n\n");
		scanf("%i",&st);
		
		
		if(st == 1)
		{
			
			
			//generate a number and automatically adds it to queue
			
			generate_customer_num();
			printf("\n\n");
			
			goto start;
		}
		
		//admin account
		else if(st == 2)
		{
					printf("\n******Good day Admin!******\n\n");
					while(1)
					{
						printf("1.View waiting Line \n\n2.Update current serving token number \n\n3.Quit\n\n");
						printf("Enter your choice: ");
						scanf("%d",&choice_admin);
				
						switch(choice_admin)
						{
							case 1:
								{
									//view the elements on the queue
									display();
									break;
								}
						
							case 2:
								{
									//remove the topmost element on the queue
									dequeue();
									break;
								}
						
							case 3:
								{
									//to exit the admin account
									printf("\n");
									goto start;
								}
						
							default:
								{
									printf("Invalid Input!");
									printf("\n\n");
								}
						}
					}
		
		}
		else if(st == 3)
		{
			exit(0);
		}
		else
		{
			printf("Invalid Input. Please try agian.");
			printf("\n\n");
			goto start;
		}
}
