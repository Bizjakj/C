#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node{
   	int data;
   	struct node *next;
};

struct node * createnode()//function to create node
{
  struct node *t;
  t=(struct node*)malloc(sizeof(struct node));
  return(t);
}

void insert( int a, struct node **head)//function to insert at first location
{
  struct node *p;
  p=createnode();
  
  p->data = a;
  p->next=NULL;
  
  if(*head==NULL)
  {
      *head=p;
  }
  else
  {
      p->next=*head;
      *head=p;
  }
}

void deletion(struct node *head)//function to delete from first position
{
	if(head->next != NULL){
		deletion(head->next);
	}
	free(head);
	
}

///// MAIN ALGORITHMIC FUNCTION to MERGE the two input linked lists ///////

void merge(struct node *head1, struct node *head2)
{
    	struct node *temp1 = head1;
    	struct node *temp2 = head2;

    	struct node *holder1 = NULL;
    	struct node *holder2 = NULL;
    	//Temporary pointer variables to store the address of next node of the two input linked list

    	while(temp1!=NULL && temp2!=NULL)
    	{
        		holder1 = temp1 -> next;
        		//Storing the address of next node of first linked list
        		temp1->next=temp2;
        		//Making the first node of first linked list point to first node of second linked list

        		if(holder1!=NULL)			{
                    //Making the first node of second linked list point to second node of first linked list
                    holder2 = temp2 -> next;
                    temp2 -> next = holder1;
		        }
        		temp1=holder1;
        		temp2=holder2;
        		//Updating the address location of two pointer variables temp1 and temp2
    	}
}

void printlist(struct node *temp){
	if(temp == NULL){
		printf("\n");
		return;
	}
    printf("%d",temp->data);
    temp=temp->next;
    while(temp!=NULL){
            printf("->%d",temp->data);
            temp=temp->next;
    }
    printf("\n");
}

int main()
{
	struct node *head1 = NULL;
	struct node *head2 = NULL;
	
	insert(1, &head1);
	insert(2, &head1);
	insert(3, &head1);
	
	insert(2, &head2);
	insert(3, &head2);
	insert(1, &head2);

	printlist(head1);
	printlist(head2);
	
	merge(head1, head2);
	
	printlist(head1);
	
	deletion(head1);
	
    return 0;
}
