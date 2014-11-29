#include <stdio.h>
#include <conio.h>
#include "LAYOUT.h"
#include "submenu.h"
#include "TEXTBOX.h"

void clear_content(void)
{
	int i,j;
	for(j=2;j<=79;j++)
	{
		if(j==27 || j==53)
			continue;
		for(i=5;i<=23;i++)
		{
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
	gotoxy(3,5+i); cprintf("%s",temp[i].name); gotoxy(29,5+i); cprintf("%s",temp[i].phone); gotoxy(55,5+i);   cprintf("%s",temp[i].address);
	}
}

int main (void)
{
	clrscr();
	background_color(0x00);
	draw_border_shortcut(1,25);
	draw_content();
	detectmouse();
	showmousetext();
	write_file("radwa.txt");
	read_file	("RA.TXT");
	display_all();
	getch();
	search_multiple_results("cairo",3);
	getch();
	display_all();
	keyboard();
	getch();
	getch();
	return 0;

			/*
  int x1,y1,x2,y2;
  int edit=0;
  char ch;
  clrscr();


  messagebox(23,9,58,17);
  detectmouse ();
  showmousetext ();
  getch();

  edit=1;
  if(edit)
  {
	gotoxy(25,13);
	txtbox(14);
	ch=getch();
   switch(ch)
   {
	case tab:
	gotoxy(25+14,13);
	txtbox(11);
	ch=getch();
	switch(ch)
	{
			case tab:
		gotoxy(25+14+12,13);
		txtbox(5);
		break;
	}
	break;

   }
  }
  getch();
  return 0;   */
}



	//
	//
	//
	//Code to test Linked List
	//
	//
	//
	/*
	char choice;
   int action;
   struct phonebook* temp;
   char var[50];
   read_file("RA.TXT");
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
   */
