#include <stdio.h>
#include <conio.h>
#include<string.h>
#include "FILE.h"
//#include "ADDNEWTX.H"
#include "ALLBOX.H"

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
#define esc 27

#define back 0X07
#define high 0X71
#define all 0X03
#define light 0X70


void menu(int x, int y,int x2,int y2,int pos2);
void submenu(int x, int y,int x2,int y2,char buffer[]);
// void keyboard ();


// the menus "file ,view ,search"

void menu(int x, int y,int x2,int y2,int pos2)
{
		char menu3[3][30]={" Search By Name "," Search By Phone "," Search By Address"};
		char menu2[3][30]={" Sort By Name "," Sort By Phone "," Sort By Address"};
		char menu[5][30]={"   New    ","   Open   " ,"   Save   " ,"  Delete  ","   Exit   "};
		int loap,loap2;
		int vpos=0,fpos=0,spos=0;
		char key;
		char buffer [4096],subbuffer [4096];
		int terminate=0;
		char * name;
		char * phone;
		char * address;
		int newcontact,editbox,viewsearch,viewresult;
		struct phonebook* temp;

		textattr(back);
		gettext(1,1,80,25,buffer);
		do
		{
	 //	clrscr();
		textattr(back);
		
		//menu File
		
		if(pos2==0)
		{
			for(loap2=0;loap2<x+3;loap2++)
			{
				for(loap=0;loap< y-2;loap++)
				{
					gotoxy(y2+loap,x2+loap2);
					textattr(light);
					cprintf("  ");
				}
			}

			for(loap=0 ;loap <5 ;loap ++)
			{
				if(fpos == loap)
					textattr(all);
				gotoxy(y2+1,x2+1+(2*loap));
				cprintf("%s",menu[loap]);
				textattr(light);
				if(loap !=4)
				{
					gotoxy(y2+1,x2+2+(2*loap));
					cprintf("-----------");
				 }

			}

					if(fpos ==1)
						gotoxy(y2+4,x2+3);

					else if(fpos ==2)
						gotoxy(y2+4,x2+5);
					else if(fpos ==3)
						gotoxy(y2+4,x2+7);
					else if(fpos==0)
						gotoxy(y2+4,x2+1);
					else
						gotoxy(y2+4,x2+9);
			  //	gotoxy(y2+4,x2+1);

		}
		
		//View Menu
		
		if(pos2==1)
		{
			for(loap2=0;loap2<x-1;loap2++)
			{
				 for(loap=0;loap< y+2;loap++)
				{
					gotoxy(y2+7+loap,x2+loap2);
					textattr(light);
					cprintf("  ");
				}
			}
			for(loap=0 ;loap<3;loap++)
			{
				if(vpos == loap)
					textattr(all);
				gotoxy(y2+8,x2+1+(2*loap));
				cprintf("%s",menu2[loap]);
				textattr(light);
				if(loap!=2)
				{
					gotoxy(y2+8,x2+2+(2*loap));
					cprintf("--------------");
				}

			}
					if(vpos ==1)
						gotoxy(y2+9,x2+3);

					else if(vpos ==2)
						gotoxy(y2+9,x2+5);
					else if(vpos ==3)
						gotoxy(y2+9,x2+7);
					else
						gotoxy(y2+9,x2+1);
		}
        
		//search menu
		if(pos2==2)
		{
			for(loap2=0;loap2<x-1;loap2++)
			{
				for(loap=0;loap< y+4;loap++)
				{
					gotoxy(y2+15+loap,x2+loap2);
					textattr(light);
					cprintf("  ");
				}
			}
			for(loap=0 ;loap<3;loap++)
			{
				if(spos == loap)
					textattr(all);
				gotoxy(y2+16,x2+1+(2*loap));
				cprintf("%s",menu3[loap]);
				textattr(light);
				if(loap !=2)
				{
				gotoxy(y2+16,x2+2+(2*loap));
				cprintf("-----------------");
				}
			}
					if(spos ==1)
						gotoxy(y2+17,x2+3);

					else if(spos ==2)
						gotoxy(y2+17,x2+5);
					else if(spos ==3)
						gotoxy(y2+17,x2+7);
					else
						gotoxy(y2+17,x2+1);
		}
		textattr(back);

		flushall();
		key=getch();
		
		// get the key from user and handle it

		switch(key)
		{
			case esc:
				puttext(1,1,80,25,buffer);
				terminate=1;
			break;

			case 0:
				key=getch();
				switch(key)
				{
					case up:
						vpos--;
						fpos--;
						spos--;
						if(spos<0)
						{
							spos=2;
						}
						if(fpos <0)
							fpos=4;
						if(vpos <0)
							vpos=2;

					break;

					case down:
						spos++;
						vpos++;
						fpos++;
						if(spos >2)
							spos=0;
						if(fpos >4)
							fpos=0;
						if(vpos >2)
							vpos=0;


					break;

					case left:
						puttext(1,1,80,25,buffer);
					  //	pos=0;
					   //	fpos=0;
						pos2--;
						if(pos2 <=0)
							pos2=0;

					break;

					case right:
						puttext(1,1,80,25,buffer);
					   //	pos=0;
					   //	fpos=0;
						pos2++;
						if(pos2>=2)
							pos2=2;
					break;

					case altf:
						  puttext(1,1,80,25,buffer);
						  pos2=0;
						  spos=0;
						  vpos=0;
						  fpos=0;
					break;

					case altv:
						puttext(1,1,80,25,buffer);
						pos2=1;
						spos=0;
						vpos=0;
						fpos=0;
					break;

					case alts:
						puttext(1,1,80,25,buffer);
						pos2=2;
						spos=0;
						vpos=0;
						fpos=0;
					break;

				}
			break;

			case enter:
				if(pos2==2)
				{
				switch(spos)
				{
					case 0:
						// y3mel call 3la el fun eli asmha search bya name
						puttext(1,1,80,25,buffer);
						name=viewsearchbox(0);
						clrscr();
					background_color(0x00);
					draw_border_shortcut(1,25);
					draw_content();
					display_all();
					 /*	//puttext(1,1,80,25,buffer);
						temp=search(name,1);
						//viewsearchresult("ssss","ccccc"," dddd ",2);
						if(lengthOfArray == 0)
							notfoundsearch(0);
						else
						{

							viewsearchresult(temp);

						}  */
						//viewsearchresult(char * name,char *phone ,char *addr,)
						//puttext(1,1,80,25,buffer);
						terminate=1 ;
					break;
					case 1:
						// y3mel call ll funcation eli asmha search by phone
						puttext(1,1,80,25,buffer);
						phone=viewsearchbox(1);
						clrscr();
					background_color(0x00);
					draw_border_shortcut(1,25);
					draw_content();
					display_all();
						//delay(100);
						//puttext(1,1,80,25,buffer);
						
						//puttext(1,1,80,25,buffer);
						terminate=1;
					break;
					case 2:
						//y3mel call ll search by address
						puttext(1,1,80,25,buffer);
						address=viewsearchbox(2);
						clrscr();
					background_color(0x00);
					draw_border_shortcut(1,25);
					draw_content();
					display_all();
						//puttext(1,1,80,25,buffer);
						
						terminate=1;
					break;

				}
				}
				
				//handle the view menu and its items when press enter
				
				if(pos2==1)
				{
				switch(vpos)
				{
					case 0:
						// y3mel call 3la el fun eli asmha sort name
						clear_content();
						sort(1);
						puttext(1,1,80,25,buffer);
						display_all();
						terminate=1 ;
					break;
					case 1:
						// y3mel call ll funcation eli asmha sort phone
						clear_content();
						sort(2);
						puttext(1,1,80,25,buffer);
						display_all();
						terminate=1;
					break;
					case 2:
						//y3mel call ll search by sort address
						clear_content();
						sort(3);
						puttext(1,1,80,25,buffer);
						display_all();
						terminate=1;
					break;

				}
				}

				//handle file menu and its items

				if(pos2==0)
				{
				switch (fpos)
				{
					case 0:
					//new in file
					
					  // gettext(1,1,80,25,subbuffer);
					  // submenu(6,18,5,4,buffer);
					   //puttext(1,1,80,25,subbuffer);
					  // terminate=1;
					break;
					
					
					case 1:
						//clear_content();
						puttext(1,1,80,25,buffer);
						read_file("RA.TXT");
						display_all();
						//gettext(1,1,80,25,buffer);
						//puttext(1,1,80,25,buffer);
						//puttext(1,1,80,25,buffer);
						terminate=1;
						
					break;

					case 2:
						write_file("RA.TXT");
						puttext(1,1,80,25,buffer);
						terminate=1;
					break;
					
					case 3:
						//Delete
					break;
					
					case 4:
						exit();
					break;

				}
				}
			break;

		}
		}while(terminate !=1);

}



/*void keyboard (){
	char key;
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
		}
		break;


	}

} */

/*
void submenu(int x, int y,int x2,int y2,char buffer[])
{
	int loap,loap2;
	int fpos=0,terminate=0;
	char key,buf[4096];
	char **contact;
	char * name={" "} ;
	char * phone ={" "}; 
	char * address ={" "};
	int newcontact,editbox;
	char smenu[2][30]={" Add New Record "," Edit Record "};
	gettext(1,1,80,25,buf);

	do
	{
		// twp for loap to plot the menu
		for(loap=0;loap<y;loap++)
		{
			for(loap2=0;loap2<x;loap2++)
			{
				gotoxy(y2+loap,x2+loap2);
				textattr(light);
				cprintf("  ");
			}
		}
		
		//fill the submenu with data

		for(loap=0 ;loap <2 ;loap ++)
		{
			if(fpos == loap)
				textattr(all);
			gotoxy(y2+1,x2+1+(2*loap));
			cprintf("%s",smenu[loap]);
			textattr(light);
			if(loap !=1)
				{
					gotoxy(y2+1,x2+2+(2*loap));
					cprintf("-----------------");
				}

		}
		
		// to set the cursor on the first char. in every menu

		if(fpos ==1)
			gotoxy(y2+2,x2+3);

		/*else if(fpos ==2)
			gotoxy(y2+2,x2+5);
		else if(fpos ==3)
		//	gotoxy(y2+2,x2+7);
		else
			gotoxy(y2+2,x2+1);  
			
			
			
		// get the key from the user
		
		key=getch();
		
		switch(key)
		{
		
		// if the user pressed ESC
			case esc:
				 puttext(1,1,80,25,buf);
				terminate=1;
			break;
        
		// the extended keys "up ,down ,altf ,altv ,alts"
			case 0:
				key=getch();
				switch(key)
				{
					case up:
						fpos--;
						if(fpos <0)
							fpos=1;
					break;

					case down:
						fpos++;
						if(fpos >1)
							fpos=0;
					break;

				 /*	case left:
						terminate=1;
					break;

					case right:
						terminate=1;
					break;  */
            
			// open the other menus
			
			/*		case altf :
						 puttext(1,1,80,25,buffer);
						menu(8,15,3,2,0);
					break;

					case altv:
					   //	terminate=1;
						puttext(1,1,80,25,buffer);
						menu(8,15,3,2,1);
						terminate=1;
					break;


					case alts:
						 puttext(1,1,80,25,buffer);
						menu(8,15,3,2,2);
					break;
				}
			break;

				case enter:

				switch(fpos)
				{
				
				// call new contact message box
					case 0:
						
						//clrscr();
						puttext(1,1,80,25,buffer);
						newContact(contact);
						//clrscr();
						//printf("name : %s phone: %s address: %s",contact[0],contact[1],contact[2]);
						//getch();
						puttext(1,1,80,25,buffer);
						terminate=1 ;
					break;
					
				// call edit message box
				
					case 1:
						// y3mel call ll funcation ll edit record
						//newContact(contact);
						puttext(1,1,80,25,buffer);
						showeditbox(name,phone,address);
						//getch();
						//puttext(1,1,80,25,buffer);
						terminate=1;
						//flushall();
					break;
				/*	case 2:
						//y3mel call ll search by phone
						
						
						terminate=1;
					break;
					case 3:
					 //
					 terminate=1;
					 break; */

//				}
	//			break;


		//} }while(terminate !=1);
	// getche();
   //	 getch();
//}


