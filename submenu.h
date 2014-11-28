#include <stdio.h>
#include <conio.h>
#include<string.h>

#define enter 13
#define up 72
#define down 80
#define right 77
#define left 75
#define altf 33
#define v  118
#define s  115
#define altv 47
#define alts 31
#define back 0X07
#define high 0X71
#define all 0X03
#define light 0X70

void submenu_file(int x, int y,int x2,int y2);
void submenu_view(int x, int y,int x2,int y2);

void submenu_search(int x, int y,int x2,int y2);


void submenu(int x, int y,int x2,int y2);

void keyboard ();

void submenu_search(int x, int y,int x2,int y2)
{
		char menu[3][30]={"search by address","search by name","search by phone"};
		int loap,loap2;
		int pos=0,pos2=2;
		char key;
		char buffer[4096];
		int terminate=0;
		textattr(back);
		gettext(1,1,80,25,buffer);
		do
		{
	 //	clrscr();
		textattr(back);

		for(loap2=0;loap2<x;loap2++)
		{
			 for(loap=0;loap< y;loap++)
				{
				gotoxy(y2+loap,x2+loap2);
				textattr(light);
				cprintf("  ");
				}
		}

		for(loap=0;loap<3;loap++)
		{

			if(pos == loap)
				textattr(all);
			gotoxy(y2+1,x2+1+(2*loap));
			cprintf("%s",menu[loap]);
			textattr(light);
			gotoxy(y2+1,x2+2+(2*loap));
			cprintf("------------------");
		}
		textattr(back);

		flushall();
		key=getch();
	  //	gettext(1,1,80,25,buffer);
		switch(key)
		{

			case 0:
				key=getch();
				switch(key)
				{
					case up:
						pos--;
						if(pos <0)
							pos=2;
					break;

					case down:
						pos++;
						if(pos >2)
							pos=0;
					break;

					case left:
						pos2--;
						if(pos2==1)
						{
						puttext(1,1,80,25,buffer);
						submenu_view(8,20,3,11);
						}
						else if(pos2 ==0)
						{
						//yshoof el file
						puttext(1,1,80,25,buffer);
						submenu_file(8,20,3,6);
						}
						else if(pos2 <0)
						{
							pos2=2;
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}

						else if(pos ==2)
						{
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}

						terminate=1;
					break;

					case right:
							pos2++;
						if(pos2==1)
						{
						puttext(1,1,80,25,buffer);
						submenu_view(8,20,3,11);
						}
						else if(pos2 ==0)
						{
						//yshoof el file
						puttext(1,1,80,25,buffer);
						submenu_file(8,20,3,6);
						}
						else if(pos2 >2)
						{
							pos2=0;
							puttext(1,1,80,25,buffer);
							submenu_file(8,20,3,6);
						}
						else
						{
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}
						terminate=1;
					break;

				}
			break;

			case enter:
				switch(pos)
				{
					case 0:
						// y3mel call 3la el fun eli asmha search bya address
						terminate=1 ;
					break;
					case 1:
						// y3mel call ll funcation eli asmha search by name
						terminate=1;
					break;
					case 2:
						//y3mel call ll search by phone
						terminate=1;
					break;

				}
			break;


		}
		}while(terminate !=1);

}

void submenu_view(int x, int y,int x2,int y2)
{
		char menu[3][30]={"sort by address","sort by name","sort by phone"};
		int loap,loap2;
		int pos=0,pos2=1;
		char key;
		int terminate=0;
		char buffer[4096];
		textattr(back);
		gettext(1,1,80,25,buffer);
		do
		{
	   //	clrscr();
		textattr(back);
	  //	gettext(1,1,80,25,buffer);
		for(loap2=0;loap2<x;loap2++)
		{
			 for(loap=0;loap< y;loap++)
				{
				gotoxy(y2+loap,x2+loap2);
				textattr(light);
				cprintf("  ");
				}
		}

		for(loap=0;loap<3;loap++)
		{

			if(pos == loap)
				textattr(all);
			gotoxy(y2+1,x2+1+(2*loap));
			cprintf("%s",menu[loap]);
			textattr(light);
			gotoxy(y2+1,x2+2+(2*loap));
			cprintf("------------------");
		}
		textattr(back);

		flushall();
		key=getch();

		switch(key)
		{

			case 0:
				key=getch();
				switch(key)
				{
					case up:
						pos--;
						if(pos <0)
							pos=2;
					break;

					case down:
						pos++;
						if(pos >2)
							pos=0;
					break;

					case left:
						pos2--;
						if(pos2==1)
						{
						puttext(1,1,80,25,buffer);
						submenu_view(8,20,3,11);
						}
						else if(pos2 ==0)
						{
						//yshoof el file
						puttext(1,1,80,25,buffer);
						submenu_file(8,20,3,6);
						}
						else if(pos2 <0)
						{
							pos2=2;
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}

						else if(pos ==2)
						{
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}

						terminate=1;
					break;

					case right:
							pos2++;
						if(pos2==1)
						{
						puttext(1,1,80,25,buffer);
						submenu_view(8,20,3,11);
						}
						else if(pos2 ==0)
						{
						//yshoof el file
						puttext(1,1,80,25,buffer);
						submenu_file(8,20,3,6);
						}
						else if(pos2 >2)
						{
							pos2=0;
							puttext(1,1,80,25,buffer);
						  //	submenu_search(8,20,3,16);
						}
						else
						{
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}
						terminate=1;
					break;

				}
			break;

			case enter:
				switch(pos)
				{
					case 0:
						// y3mel call 3la el fun eli asmha sort bya address
						terminate=1 ;
					break;
					case 1:
						// y3mel call ll funcation eli asmha sort by name
						terminate=1;
					break;
					case 2:
						//y3mel call ll sort by phone
						terminate=1;
					break;

				}
			break;

		}
		}while(terminate !=1);
}

void submenu_file(int x, int y,int x2,int y2)
{
		char menu[3][30]={"open","delete","edit"};
		int loap,loap2;
		int pos=0,pos2=0;
		char key;
		char buffer[4096];
		int terminate=0;
		textattr(back);
		gettext(1,1,80,25,buffer);
		do
		{
	 //	clrscr();
		textattr(back);

		for(loap2=0;loap2<x;loap2++)
		{
			 for(loap=0;loap< y;loap++)
				{
				gotoxy(y2+loap,x2+loap2);
				textattr(light);
				cprintf("  ");
				}
		}

		for(loap=0;loap<3;loap++)
		{

			if(pos == loap)
				textattr(all);
			gotoxy(y2+1,x2+1+(2*loap));
			cprintf("%s",menu[loap]);
			textattr(light);
			gotoxy(y2+1,x2+2+(2*loap));
			cprintf("------------------");
		}
		textattr(back);

		flushall();
		key=getch();
	  //	gettext(1,1,80,25,buffer);
		switch(key)
		{

			case 0:
				key=getch();
				switch(key)
				{
					case up:
						pos--;
						if(pos <0)
							pos=2;
					break;

					case down:
						pos++;
						if(pos >2)
							pos=0;
					break;


					case left:
						pos2--;
						if(pos2==1)
						{
						puttext(1,1,80,25,buffer);
						submenu_view(8,20,3,11);
						}
						else if(pos2 ==0)
						{
						//yshoof el file
						puttext(1,1,80,25,buffer);
						submenu_file(8,20,3,6);
						}
						else if(pos2 <0)
						{
							pos2=2;
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}

						else if(pos ==2)
						{
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}

						terminate=1;
					break;

					case right:
							pos2++;
						if(pos2==1)
						{
						puttext(1,1,80,25,buffer);
						submenu_view(8,20,3,11);
						}
						else if(pos2 ==0)
						{
						//yshoof el file
						puttext(1,1,80,25,buffer);
						submenu_file(8,20,3,6);
						}
						else if(pos2 >2)
						{
							pos2=0;
							puttext(1,1,80,25,buffer);
						  //	submenu_search(8,20,3,16);
						}
						else
						{
							puttext(1,1,80,25,buffer);
							submenu_search(8,20,3,16);
						}
						terminate=1;
					break;


				}
			break;

			case enter:
				switch(pos)
				{
					case 0:
						// y3mel call 3la el fun eli asmha search bya address
						terminate=1 ;
					break;
					case 1:
						// y3mel call ll funcation eli asmha search by name
						terminate=1;
					break;
					case 2:
						//y3mel call ll search by phone
						terminate=1;
					break;

				}
			break;


		}
		}while(terminate !=1);

}

void keyboard (){
	char key;
	key=getch();

	switch(key)
	{

		 case 0:
			key=getch();
			switch(key)
			{

				case altf :
				 submenu_file(8,20,3,5);
			   break;

			case altv:
			submenu_view(8,20,3,11);
			break;


			case alts:
			submenu_search(8,20,3,16);
			break;
		}
		break;


	}

}