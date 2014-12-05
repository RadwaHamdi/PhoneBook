#include <stdio.h>
#include <conio.h>
#include<string.h>
#include "submenu.h"
//#include "line.h"

#define enter 13
#define up 72
#define down 80
#define right 77
#define left 75
#define altf 33
#define altv 47
#define alts 31
#define esc 27
#define f2  60
#define insert 82
#define del  83



 void keyboard (void)
 {
	char key;
	char * name={" "} ;
	char * phone ={" "}; 
	char * address ={" "};
  //	int x1=3,y=5,x2=25,x3=55;
	
while(1)
{
	flushall();
	key=getch();

	switch(key)
	{
		case 0:
			key=getch();
			switch(key)
			{
				case altf :
					menu(8,15,3,2,0);
				break;

				case altv:
					menu(8,15,3,2,1);
				break;

				case alts:
					menu(8,15,3,2,2);
				break;

				case insert:
				   //  add new record message box;
					if(get_last_index() < 19)
				   		newContact();
						//clrscr();
					//printf("name : %s phone: %s address: %s",contact[0],contact[1],contact[2]);
				break;

				case del:
					deleteRecordMessage();
				break;

			 	case f2:
                    showeditbox(name,phone,address);
				break; 
				
				case up:
					if(i!=1)
					{
						normal_line(i);
						i=i-1;
						highlight_line(i);
					}
				break;
				
				case down:
					if(i!=get_last_index())
					{
						normal_line(i);
						i=i+1;
						highlight_line(i);
					}
					//clrscr();
				break;

			   }
				break;

		}



}
 }