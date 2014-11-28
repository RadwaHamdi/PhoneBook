#include<stdio.h>
#include<conio.h>

struct phonebook
{
	char name[80];
	char phone[20];
	char address[30];
	struct phonebook * prev;
	struct phonebook * next;
};

struct phonebook* head=NULL;
struct phonebook* tail=NULL;



struct phonebook* create_node(void);
void append_node(struct phonebook*);
struct phonebook* search_node(char*);
void delete_list(void);
void delete_node(char*);
void display_all(void);
int insert_node(struct phonebook*);
void swap_elements(struct phonebook*,struct phonebook*);
void sort(int);//1 for phone 2 for address

struct phonebook* create_node(void)
{
	return((struct phonebook *)malloc(sizeof(struct phonebook)));
}

void append_node(struct phonebook *element)
{
	if(!head)
	{
		head=tail=element;
		element->prev=NULL;
		element->next=NULL;
	}
	else
	{
		tail->next=element;
		element->prev=tail;
		tail=element;
		element->next=NULL;
	}
}

/*
struct phonebook* search_node_int(int key)
{
	struct phonebook *temp=head;
	while(temp&&temp->id!=key)
	{
		temp=temp->next;
	}
	return temp;
}

*/
struct phonebook* search_node(char *key)
{
	struct phonebook *temp=head;
	while(temp&&strcmp(temp->name,key))
	{
		temp=temp->next;
	}
	return temp;
}



void delete_list(void)
{
	struct phonebook * temp;
	while(head != NULL)
	{
		temp=head;
		head=head->next;
		free(temp);
	}
	tail=NULL;
}

void delete_node(char * key)
{
	struct phonebook *temp;
	temp=search_node(key);
	if(temp!=NULL)
	{
		if(temp==head && head==tail)
		{
			head=tail=NULL;
			free(temp);
		}
		else if(temp==head && head!=tail)
		{
			head=head->next;
			head->prev=NULL;
			free(temp);
		}
		else if(temp==tail && head!=tail)
		{
			tail=tail->prev;
			tail->next=NULL;
			free(temp);
		}
		else
		{
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			free(temp);
		}
	}
}

void display_all(void)
{
	struct phonebook *temp=head;
	int counter=1;
	while(temp)
	{

		printf("\nthe %d th employee has name=%s phone=%s address=%s",counter,temp->name,temp->phone,temp->address);
		temp=temp->next;
		counter++;
	}
}

int insert_node(struct phonebook * node)
{
	 struct phonebook *temp=head;
	 //empty list
	 if(head==tail && head==NULL)
	 {
				   node->next=NULL;
				   node->prev=NULL;
				   head=node;
				   tail=node;
				   return 1;
	 }
	 //only one element exist && insertion is done after it
	 else if(head==tail && head!=NULL && strcmp(node->name,head->name)>0)
	 {
			   tail=node;
			   head->next=node;
			   node->prev=head;
			   node->next=NULL;
			   return 1;
	 }
	 //insert in first location
	 else if(strcmp(node->name,head->name)<0)
	 {
		  node->next=head;
		  head->prev=node;
		  head=node;
		  node->prev=NULL;
		  return 1;
	 }
	 else
		 {
		 while(temp&&strcmp(node->name,temp->name)>0)
		 {
			   //add at last position
			   if(temp==tail && strcmp(node->name,temp->name)>0)
			   {
					  tail->next=node;
					  node->prev=tail;
					  node->next=NULL;
					  tail=node;
					  return 1;
			   }
			   else
			   {
					  temp=temp->next;
			   }
		 }
		 //add in middle
		 temp->prev->next=node;
		 node->prev=temp->prev;
		 temp->prev=node;
		 node->next=temp;
		 return 1;
	 }
}

					   /*
int key_exist(char **array,int size,char *key)
{
	int i;
	for(i=0;i<size;i++)
	{
		if(array[i]==key)
			return 1;
	}
	return 0;
}
					 */
void swap_elements(struct phonebook* elem1,struct phonebook* elem2)
{
	char temp_name[80];
	char temp_phone[20];
	char temp_address[30];

	strcpy(temp_name,elem1->name);
	strcpy(temp_phone,elem1->phone);
	strcpy(temp_address,elem1->address);

	strcpy(elem1->name,elem2->name);
	strcpy(elem1->phone,elem2->phone);
	strcpy(elem1->address,elem2->address);

	strcpy(elem2->name,temp_name);
	strcpy(elem2->phone,temp_phone);
	strcpy(elem2->address,temp_address);
}


//1 for sorting by phone
//2 for sorting by address
void sort(int choice)
{
	struct phonebook* i;
	struct phonebook* j;

	if(choice ==1)
	{
		for(i=head;i!=tail;i=i->next)
		{
			for(j=i->next;j!=NULL;j=j->next)
			{
				if(strcmp(i->phone,j->phone) >0 )
				{
					swap_elements(i,j);
				}
			}
		}
	}
	else if(choice ==2)
	{
		for(i=head;i!=tail;i=i->next)
		{
			for(j=i->next;j!=NULL;j=j->next)
			{
				if(strcmp(i->address,j->address) >0 )
				{
					swap_elements(i,j);
				}
			}
		}
	}

	display_all();

	for(i=head;i!=tail;i=i->next)
	{
		for(j=i->next;j!=NULL;j=j->next)
		{
			if(strcmp(i->name,j->name) >0 )
			{
				swap_elements(i,j);
			}
		}
	}
}

/*
void main(void)
{
   char choice;
   int action;
   struct phonebook* temp;
   char var[50];
   do
   {
		clrscr();
		do
		{
			printf("choose an action\n1 for add an employee at the last\n2 for search an employee by id\n3 for delete an employee\n4 for delete the whole list\n5 for display all\n6 for sorting the data based on the name:  ");
			flushall();
			scanf("%d",&action);
		}while(action!=1 && action!=2 && action!=3 && action!=4 && action!=5 && action!=6);

		switch(action)
		{
			case 1:
				temp=create_node();

				do
				{
					printf("\nenter the name: ");
					flushall();
					gets(var);
					strcpy(temp->name,var);
					if(search_node(var)!=NULL)
					{
						printf("this name exist!!");
					}
				}while(search_node(var)!=NULL);

				printf("enter the phone: ");
				flushall();
				gets(var);
				strcpy(temp->phone,var);

				printf("enter the address: ");
				flushall();
				gets(var);
				strcpy(temp->address,var);

				insert_node(temp);

				break;
			case 2:
				printf("Please enter the id you want to search for: ");
				flushall();
				gets(var);
				temp=search_node(var);
				if(temp!=NULL)
					printf("The employee is found with data \nname=%s\nphone=%s\naddress=%s",temp->name,temp->phone,temp->address);
				else
					printf("No employee with this id");
				break;
			case 3:
				printf("Please enter the id you want to delete: ");
				flushall();
				scanf("%d",&var);
				delete_node(var);
				break;
			case 4:
				delete_list();
				break;
			case 5:
				display_all();
				break;
			case 6:
				sort(1);
				break;
		}
		printf("\nenter 'x' to exit or any other char to make another action");
		choice=getch();
   }while(choice!='x');
}
*/