/*Includes structure for a node which can be use to make new nodes of the Linked List.
  It is assumed that the data in nodes will be an integer, though
  function can be modified according to the data type, easily.
  deleteNode deletes a node when passed with a key of the node.
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node
{
 int info;
 struct node *link;
};
struct node *start=NULL;

///////////////////////////////////////////////////////////
struct node * createnode()//function to create node
{
  struct node *t;
  t=(struct node*)malloc(sizeof(struct node));
  return(t);
}
////////////////////////////////////////////////////////
void insert( int a)//function to insert at first location
{
  struct node *p;
  p=createnode();
  
  p->info = a;
  p->link=NULL;
  
  if(start==NULL)
  {
      start=p;
  }
  else
  {
      p->link=start;
      start=p;
  }
}
///////////////////////////////////////////////////////////
void deletion()//function to delete from first position
{
    struct node *t;
    if(start==NULL)
    {
        printf("\nlist is empty");
    }
    else
    {
        struct node *p;
        p=start;
        start=start->link;
        free(p);
    }
}
///////////////////////////////////////////////////////
void viewlist()//function to display values
{
    struct node *p;
    if(start==NULL)
    {
        printf("list is empty\n");
    }
    else
    {   p=start;
        while(p!=NULL)
        {
            printf("%d ",p->info);
            p=p->link;
        }
    }
}

int main(){
	insert(12);
	insert(2);
	insert(7);
	
	viewlist();
	
	deletion();
	deletion();
	deletion();
}