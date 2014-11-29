#include <stdio.h>
#include <conio.h>
#include<string.h>
#include "submenu.h"

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
#define delete  83


 void keyboard (void)
 {
	char key;
  //	int x1=3,y=5,x2=25,x3=55;
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
				break;

				case del:
					//delete record
				break;

			 /*	case f2:

				break; */

			   }
				break;

		}



 }