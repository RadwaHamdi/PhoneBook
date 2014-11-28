#include <stdio.h>
#include <conio.h>

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

struct phonebook * create_phonebook (void);
void append_phonebook (struct phonebook * ele);
struct phonebook *  search_phonebook (char * name);
void delete_phonebook (char * key) ;
void deletelist(void);
void printlist_search (void) ;
void write_file(char fileName []);

void background_color(int color)
{

	textattr(color);
	clrscr();
	textattr(NORMAL);
}

void add_shortcut(void)
{
	textattr(0x03);
	cprintf("F2");
	textattr(0x0F);
	cprintf("  Edit Contact");
	textattr(0x03);
	cprintf("  INSERT");
	textattr(0x0F);
	cprintf("   Add Contact");
	textattr(0x03);
	cprintf("  DELETE");
	textattr(0x0F);
	cprintf("  Delete Contact");
}

void add_menus(void)
{
	textattr(0x03);
	cprintf("F");
	textattr(0x0F);
	cprintf("ile    ");
	textattr(0x03);
	cprintf("V");
	textattr(0x0F);
	cprintf("iew    ");
	textattr(0x03);
	cprintf("S");
	textattr(0x0F);
	cprintf("earch");
}

void draw_border_shortcut(int x , int y)
{
	int i,j;
	for(i=2;i<=25;i++)
	{
		for(j=2;j<=80;j++)
		{
			gotoxy(j,i);


			//if(i==2 && j==2)	printf("%c",201);
			if(i==3 && j==80)	printf("%c",187);
			//else if(i==25 && j==2)  printf("%c",200);
			else if(i==25 && j==80)	printf("%c",188);
			else if(j==80 && i!=2)  printf("%c",186);
			else if(i==3 || i==25)  printf("%c",205);
		}
	}

	/*
	gotoxy(80,25); printf("%c",188);
	*/
//	gotoxy(1,1); printf("%c",201);
	gotoxy(1,2); printf("%c",201);
	gotoxy(1,3); printf("%c",186);
	gotoxy(1,4); printf("%c",186);
	gotoxy(1,5); printf("%c",186);
	gotoxy(1,6); printf("%c",186);
	gotoxy(1,7); printf("%c",186);
	gotoxy(1,8); printf("%c",186);
	gotoxy(1,9); printf("%c",186);
	gotoxy(1,10); printf("%c",186);
	gotoxy(1,11); printf("%c",186);
	gotoxy(1,12); printf("%c",186);
	gotoxy(1,13); printf("%c",186);
	gotoxy(1,14); printf("%c",186);
	gotoxy(1,15); printf("%c",186);
	gotoxy(1,16); printf("%c",186);
	gotoxy(1,17); printf("%c",186);
	gotoxy(1,18); printf("%c",186);
	gotoxy(1,19); printf("%c",186);
	gotoxy(1,20); printf("%c",186);
	gotoxy(1,21); printf("%c",186);
	gotoxy(1,22); printf("%c",186);
	gotoxy(1,23); printf("%c",186);
	gotoxy(1,24); printf("%c",200);

//	gotoxy(1,25); printf("%c",200);
	gotoxy(x,y);
	add_shortcut();

	for(i=1;i<=80;i++)
	{
		gotoxy(i,1);
		textattr(0x00);
		cprintf(" ");
	}
	gotoxy(1,1);
	add_menus();
}


int main (char ** argv, int argc)
{
	clrscr();
	background_color(0x70);
	draw_border_shortcut(1,25);
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

