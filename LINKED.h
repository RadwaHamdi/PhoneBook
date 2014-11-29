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

int lengthOfArray;

void clear_content(void);
void search_multiple_results(char*,int);
struct phonebook* create_node(void);
void append_node(struct phonebook*);
struct phonebook* search_node(char*);
struct phonebook* search(char *,int);//1 for name 2 for phone 3 for address
void delete_list(void);
void delete_node(char*);
void display_all(void);
int insert_node(struct phonebook*);
void swap_elements(struct phonebook*,struct phonebook*);
void sort(int);//1 for phone 2 for address

void clear_content(void)
{
	int i,j;
	for(j=2;j<=79;j++)
	{
		if(j==27 || j==53)
			continue;
		for(i=5;i<=23;i++)
		{
			textattr(0x00);
			gotoxy(j,i); cprintf(" "); gotoxy(j,i); cprintf(" "); gotoxy(j,i); cprintf(" ");
		}
	}
}

void search_multiple_results(char *key,int typeOfSearch)
{
	struct phonebook *temp;
	int i;

		temp=search(key,typeOfSearch);

	clear_content();

	for(i=0;i<lengthOfArray;i++)
	{
	textattr(0x0F);
	gotoxy(3,5+i); cprintf("%s",temp[i].name); gotoxy(29,5+i); cprintf("%s",temp[i].phone); gotoxy(55,5+i);   cprintf("%s",temp[i].address);
	}
}


struct phonebook* search(char *key,int choice)
{
	struct phonebook * found;
	struct phonebook * temp;
	int index=0;

	lengthOfArray=0;
	if(choice==1)
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->name,key)==0)
						lengthOfArray++;
		}
	}
	else if(choice==2)
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->phone,key)==0)
						lengthOfArray++;
		}
	}
	else if(choice==3)
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->address,key)==0)
						lengthOfArray++;
		}
	}


	found =(struct phonebook*)malloc(lengthOfArray*sizeof(struct phonebook));

	if(choice==1)
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->name,key)==0)
			{
				strcpy(found[index].name,temp->name);
				strcpy(found[index].phone,temp->phone);
				strcpy(found[index].address,temp->address);
				index++;
			}
		}
	}
	else if(choice==2)
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->phone,key)==0)
			{
				strcpy(found[index].name,temp->name);
				strcpy(found[index].phone,temp->phone);
				strcpy(found[index].address,temp->address);
			index++;
			}
		}
	}
	else if(choice==3)
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->address,key)==0)
			{
				strcpy(found[index].name,temp->name);
				strcpy(found[index].phone,temp->phone);
				strcpy(found[index].address,temp->address);
			index++;
			}
		}
	}
	return found;
}

void create_add_node(char* temp_name,char* temp_phone,char* temp_address)
{
	struct phonebook* new_node;
	new_node=create_node();

	strcpy(new_node->name,temp_name);
	strcpy(new_node->phone,temp_phone);
	strcpy(new_node->address,temp_address);

	insert_node(new_node);
}

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
	int counter=5;
	clear_content();
	while(temp)
	{
		gotoxy(3,counter);
		textattr(0x0F);
		cprintf("%s",temp->name);

		gotoxy(29,counter);
		textattr(0x0f);
		cprintf("%s",temp->phone);

		gotoxy(55,counter);
		textattr(0x0f);
		cprintf("%s",temp->address);

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


//1 for sorting by name
//2 for sorting by phone
//3 for sorting by address
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
				if(strcmp(i->name,j->name) >0 )
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
				if(strcmp(i->phone,j->phone) >0 )
				{
					swap_elements(i,j);
				}
			}
		}
	}
	else if(choice ==3)
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