#include <stdio.h>
#include <conio.h>
#include "LAYOUT.h"
#include "keyboard.h"
#include "TEXTBOX.h"
#include "addnewtx.h"
int main (void)
{
	char name[80],phone[20],address[30];
		char **contact;
	clrscr();
	background_color(0x00);
	draw_border_shortcut(1,25);
	draw_content();
	detectmouse();
	showmousetext();

	newContact(contact);
	printf("name : %s phone: %s address: %s",contact[0],contact[1],contact[2]);
	//write_file("radwa.txt");
	read_file("RA.TXT");
	display_all();
	getch();
	search_multiple_results("cairo",3);
	getch();
	display_all();
   //	gets(name);
   //	gets(phone);
   //	gets(address);
   //	create_add_node(name,phone,address);
   //	write_file("RA.TXT");
	keyboard();
	getche();
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
  return 0; */
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
