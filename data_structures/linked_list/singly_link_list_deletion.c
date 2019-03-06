/*Includes structure for a node which can be use to make new nodes of the Linked List.
  It is assumed that the data in nodes will be an integer, though
  function can be modified according to the data type, easily.
  deleteNode deletes a node when passed with a key of the node.
*/
#include<stdio.h>
#include<assert.h>
struct node
{int info;
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
  /*printf("\nenter the number to insert");
  scanf("%d",&p->info);
  */
  
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
void deleteion()//function to delete from first position
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
//////////////////////////////////////////////////////////////////////

/*int main()
{
    int n;
    while(1)
    {
        printf("\n1.add value at first location");
        printf("\n2.delete value from first location");
        printf("\n3.view value");
        printf("\nenter your choice");
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            insert();
            break;
        case 2:
            deleteion();
            break;
        case 3:
            viewlist();
            break;
        default:
            printf("\ninvalid choice");
        }
    }
  return(0);
}


int main(){
  start = createnode();
  struct node* og = start;
  insert();
  assert(og != start);
  insert();
  printf("List:\n");
  viewlist();
  printf("\n");
  deleteion();
  deleteion();
  assert(og == start);
  deleteion();
  printf("List:\n");
  viewlist();
}

*/

int main(){
	int a = 1;
	int b = 3; 
	int c = 9;
	int d = 0;
	
	insert(a);
	
	viewlist();
	printf("\n");
	
	insert(b);
	
	viewlist();
	printf("\n");
	
	deleteion();
	insert(d);
	
	viewlist();
	printf("\n");
	
	insert(c);
	insert(d);
	viewlist();
	printf("\n");
	
	deleteion();
		viewlist();
	printf("\n");
	deleteion();
	
		viewlist();
	printf("\n");
	deleteion();
		viewlist();
	printf("\n");
	deleteion();
		viewlist();
	printf("\n");
	
		deleteion();

	
}