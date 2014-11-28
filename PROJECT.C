#include <stdio.h>
#include <conio.h>
#include "LAYOUT.h"


#define NORMAL 0x07

struct phonebook {

	char name [80];
	char phone[20];
	char address[30];
	struct phonebook * next ;
	struct phonebook * prev;
};


struct phonebook * head=NULL;
struct phonebook * tail=NULL;

//linked list functions
struct phonebook * create_phonebook (void);
void append_phonebook (struct phonebook * ele);
struct phonebook *  search_phonebook (char * name);
void delete_phonebook (char * key) ;
void deletelist(void);
void printlist_search (void) ;

//file functions
void write_file(char fileName []);



int main (void)
{
	clrscr();
	background_color(0x70);
	draw_border_shortcut(1,25);
	detectmouse();
	showmousetext();
	getche();
	getch();
	return 0;
}


struct phonebook * create_phonebook (void)

{

		return ((struct phonebook *) malloc (sizeof(struct phonebook)));

}

void append_phonebook (struct phonebook * ele)
{
	if(head == NULL)
	{
		head=tail=ele;
		ele -> prev =NULL;
		ele -> next =NULL;

	}
	else
	{
		tail -> next=ele;
		ele -> prev=tail;
		tail=ele;
		ele ->next= NULL;

	}

}
struct phonebook * search_phonebook (char * name)
{
	struct phonebook * temp=head;

	while (temp!=NULL && strcmp(temp -> name,name) )
	{
		 temp=temp -> next;
	}

	   return temp;
}

void deletelist(void)
{
	struct phonebook * temp;
	while(head != NULL)
		{
			temp=head;
			head=head -> next;
			free(temp);
		}

	   tail=NULL;
}
void delete_phonebook (char * key)
{
			struct phonebook * temp;
	temp=search_phonebook (key);

	if(temp != NULL)
	{
		if(temp == head && head ==tail)
		{
			head=tail=NULL;
			free(temp);
		}

		if(head == temp && head != tail)
		{
			head=head -> next;
			head -> prev =NULL;
			free(temp);
		}

		if(tail == temp && head != tail)
		{
			   tail = tail -> prev;
			   tail -> next =NULL;
			   free(temp);

		}

		else
		{
			temp -> prev -> next =temp -> next;
			temp -> next -> prev =temp -> prev;
			free(temp);


		}
	}
}

void printlist_search (void)
{
	struct phonebook * ptr = head;

	printf("\n the list is : \n");
	while(ptr != NULL)
	{
		 printf("\n %S \n",ptr->name);
		 ptr=ptr->next;

	}

}

//write in a file function this function receives file mame as input param
//and it writes my linked list of phonebook records in it
void write_file(char fileName [])
{
  FILE *fp;
   struct phonebook node;
	struct phonebook * tempstruct = head;


	fp = fopen(fileName, "w+");

   while(tempstruct!=NULL)
   {
	 fflush(fp);
   //	fwrite(tempstruct, sizeof(struct phonebook ), 3, fp);
	   fprintf(fp,"%s,%s,%s  \n",tempstruct->name,tempstruct->phone,tempstruct->address);
   //   fprintf(fp, "\n  Testing...\n");
	  tempstruct = tempstruct->next;
   }
   fclose(fp);
}

