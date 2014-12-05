# include<stdio.h>
# include<conio.h>
# include <stdio.h>
# include <conio.h>
# include <dos.h>
# include "hossamtextbox.h"

/* ..ASCII and Scan Codes of Keys.. */

# define ESC 27
# define ENTER 13
# define RIGHT 77
# define LEFT 75
# define HOME 71
# define END 79
# define INSERT 82
# define DEL 83
#define tab 9

void rectborder(int,int,int,int);
void hline(int,int,int);
void vline(int,int,int);
union REGS in_regs, out_regs;

void detectmouse (void)
{

	in_regs.x.ax = 0;
	int86 (0X33,&in_regs,&out_regs);
  //	if (out_regs.x.ax == 0)
 //	printf ("\n Mouse Fail To Initialize");
  //	else
	//	printf ("\n Mouse Succesfully Initialize");
}

void showmousetext (void)
{

	in_regs.x.ax = 1;
	int86 (0X33,&in_regs,&out_regs);
}

int mouse_press(void){
	in_regs.x.ax = 3;
	int86(0x33,&in_regs,&out_regs);
	return(out_regs.x.bx);
		}

int mouse_pos(int lef,int righ,int top,int bottom)
{
	in_regs.x.ax = 3;
	int86(0x33,&in_regs,&out_regs);
	return((out_regs.x.cx>lef && out_regs.x.cx<righ) &&
		   (out_regs.x.dx>top  && out_regs.x.dx<bottom));
}

/*-------------------------------------   ..Checks the status of Insert Key..   ..Returns..   ..1 if ON..   ..0 if OFF..--------------------------------------*/
int ins_state ( void )
{
  unsigned char far *stat =(char far*)0x417 ;

  char status ;

  status = *stat ;

  if ( ( status & 128 ) == 128 )
	 return 1;
  else return 0;
}

/*----------------------------------    ..Changes the shape of cursor..------------------------------------*/
void cursor_shape ( int y , int x )
{
	union REGS i, o ;
	i.h.ah = 1 ;
	i.h.ch = y ;
	i.h.cl = x ;
	int86 ( 16, &i, &o ) ;
}

/*-----------------------------------------------    ..Restores the screen to the orginal state..-------------------------------------------------*/
void restore_ui(void)
{
  int i;
  char far *vidmem=(char far*)0xB8000000;

  window(1,1,80,25);
  clrscr();

  for (i=1;i<4000;i+=2)
	  *(vidmem+i)=7;

  _setcursortype(_NORMALCURSOR);
}

/*-------------------------------------------    ..Function for drawing horizontal line..---------------------------------------------*/
void horiz_draw(int start_x,int end_x,int y,char symbol)
{
 int i,len;
 len=end_x-start_x;

 for (i=1;i<=len+1;++i,++start_x)
 {
   gotoxy(start_x,y);
   cprintf("%c",symbol);
 }
}

/*-----------------------------------  ..The important fuction..  ..Just include in your programs..-----------------------------------+------------------------- Available Keys -----------------------------------+|    ~ Right Arrow --> For moving the cursor to the right                 ||    ~ Left  Arrow --> For moving the cursor to the left                  ||    ~ DEL         --> For deleting characters                            ||    ~ Backspace   --> For deleting characters                            ||    ~ Insert      --> For inserting charcters                            ||    ~ Home           --> For going to the beginning of the text             ||    ~ End         --> For going to the end of the text                   ||    ~ ESC           --> For clearing the textbox                 |+----------------------------------------------------------------------------+*/
char * txtbox ( int length )
{
   char str[80];  /*              ..Array into which characters are being stored,               the length of the string is limited to 80..             ..Just change the length to meet your needs..             ..You can even use dynamic memory allocation, if you               are poor in memory..          */char key;

   int startx,    /* ..For storing the starting position.. */
	   x,
	   y,
	   i,
	   j,
	   currentpos,
	   lastpos = 0,
	   len;      /* ..Length of the string.. */

   startx = wherex();
   y = wherey();

/*I have used the colors which I like, you are free to use your      own colors..----------------------------------------------------------------------*/

   textcolor ( WHITE );
   textbackground ( BLUE );

   /* ..Just for drawing the cute blue box.. */
   horiz_draw ( startx , startx + length , y , ' ');

   gotoxy ( startx , y );
   str[0] = '\0';

   while ( 1 )
   {
	  if (  ins_state() == 1 ) /* ..If the Insert is ON change the cursor.. */
	  cursor_shape ( 4 , 8 );
	  else
	  _setcursortype( _NORMALCURSOR );

	  key = getch();
	  x = wherex();
	  len = strlen ( str );

	  if ( key == ENTER )
	 break;

	  if ( key == ESC ) /* ..For clearing the characters in the textbox.. */
	  {
	 textbackground ( BLUE );
	 horiz_draw ( startx , startx + length , y , ' ');
	 gotoxy ( startx , y );
	 str[0] = '\0';
	 lastpos = 0;
	 continue;
	  }

	  /* ..For storing the typed characters into the array.. */if ( key > 31 && key < 127 && x < ( startx + length ) )
	  {
	 if ( len == length && ins_state() == 1 )
	 {
		 printf ( "\a" );
		 continue;
	 }

	 if (  ins_state() == 1 )  /* ..Insert.. */
	 {
	currentpos = x - startx;
	str[len + 1] = '\0';

	for ( i = len ; i >= currentpos ; i-- )
	str[i] = str[i - 1];

	str[currentpos] = key;
	len = strlen ( str );
	gotoxy ( startx , y );
	horiz_draw ( startx , startx + len , y , ' ');
	gotoxy ( startx , y );

	for ( i = 0 ; i < len ; i++ )
	   putch ( str[i] );

	gotoxy ( x , y );
	 }
	 else
	 {
	   i = x - startx;
	   putch ( key );

	   str[i] = key;

	   if ( i >= lastpos )
	   {
	  lastpos = i;
	  str[++i] = '\0';
	   }
	 }
	  }

	  if ( key == 8 && x <= startx + len && x != startx ) /* ..Backspace.. */
	  {
	 x = wherex();
	 currentpos = x - startx;

	 for ( i = currentpos - 1 ; str[i] != '\0' ; i++ )
	 str[i] = str[i + 1];

	 gotoxy ( startx , y );
	 horiz_draw ( startx , startx + len , y , ' ');
	 gotoxy ( startx , y );

	 for ( i = 0 ; i < len ; i++ )
	 putch ( str[i] );

	 gotoxy ( --x , y );
	 continue;
	  }

	  if ( key == 0 )   /* ..If the keys are Scan Keys.. */
	  {
	 key = getch();

	 if ( key == END )
	 {
	 gotoxy ( startx + len , y );
	 continue;
	 }

	 if ( key == HOME )
	 {
	 gotoxy ( startx , y );
	 continue;
	 }

	 if ( key == LEFT && x > startx )
	 {
	 gotoxy ( --x , y );
	 continue;
	 }

	 if ( key == RIGHT && x < startx + len )
	 {
	 gotoxy ( ++x , y );
	 continue;
	 }

	 x = wherex();

	 if ( key == DEL &&  x != startx + len )
	 {
	x = wherex();
	currentpos = x - startx;

	for ( i = currentpos ; str[i] != '\0' ; i++ )
	   str[i] = str[i + 1];

	gotoxy ( startx , y );
	horiz_draw ( startx , startx + len , y , ' ');
	gotoxy ( startx , y );

	for ( i = 0 ; i < len ; i++ )
	   putch ( str[i] );

	gotoxy ( x , y );
	continue;
	 }
	  }
   }  /* ..End of while loop.. */

   i = strlen ( str );

   /* ..Truncates the useless spaces found at the end of string.. */
   for ( j = i - 1 ; j >= 0 ; --j )
   {
	  if ( str[j] != ' ' )
	  {
	 str[++j] = '\0';
	 break;
	  }
   }

   return str;

}

void fillrect(int x1,int y1,int x2,int y2)
{
	int m,l,i,j;
	for(i=y1;i<y2;i++)
	{
		gotoxy(x1,i);
		for(j=x1;j<x2;j++)
		{
			cprintf(" ");
		}
	}
}
void button(int x1,int y1,char * btxt)
{
	gotoxy(x1,y1);
	textbackground(GREEN);
	fillrect(x1,y1,x1+8,y1);
	gotoxy(x1+1,y1);
	textcolor(BLACK);
	cprintf("%s",btxt);
}
void messagebox(int x1,int y1,int x2,int y2)
{
	char name[]="";
	char tele[]="";
	char address[]="";
	textbackground(BLACK);
     //	fillrect(0,0,80,30);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1);
	textbackground(BLUE);
	fillrect(x1+2,y1+2,x2-1,y2-1);

	//textbackground();

	//button(x1+3,y2-1,"DELETE");
	button(x1+12,y2-1,"DONE");
	//button(x1+21,y2-1,"NEXT");
	gotoxy(x1+2,y1+2);
	textbackground(GREEN);
	textcolor(WHITE);
	cprintf("Name         Telephone   Address\n");
	gotoxy(x1+2,y1+4);
	textcolor(YELLOW);
	textbackground(BLUE);
	cprintf("%s  %s   %s",name,tele,address);
	gotoxy(x1+4,y2-1);
}
void editmode()
{

}
 void newContact(char ** contact)
{
	int terminate=0;
	int x=7,y=11,i=0;
	char ch,ch2;
	messagebox(5,7,40,15);
	detectmouse();
	showmousetext();
	  gotoxy(x,y);
	  contact[0]=/*txtbox(14)*/run_textbox(x,y,14,1);
	  x+=14;
	  do
	  { 
	    ch=getch();
		switch(ch)
		{

			case tab:
				gotoxy(x,y);
				contact[1]=run_textbox(x,y,12,1);
				ch=getch();
				 x+=12;
				 switch(ch)
				 {
					case tab:
					   gotoxy(x,y);
					   contact[2]=run_textbox(x,y,5,1);
					   ch=getch();
					   switch(ch)
					   {
					   		case tab:
					   			gotoxy(9,14);
					   			button(x1+3,y2-1,"DONE",1);
								button(x1+12,y2-1,"CANCEL",0);
					   			ch=getch();
					   			switch(ch)
					   			{

					   				case tab:
					   					gotoxy(18,14);
					   					button(x1+3,y2-1,"DONE",0);
										button(x1+12,y2-1,"CANCEL",1);
					   					ch2=getch();
					   					switch(ch2)
					   					{
					   						case ENTER:
					   							terminate=1;
					   							break;
					   						case tab:
					   							terminate=2;
					   							break;
					   					}
					   					break;
					   				case ENTER:
					   					create_add_node(contact[0],contact[1],contact[2]);
					   					terminate=1;
					   					break;
					   			}
					   }
					   break;
				}
				break;
		}
	   }while(terminate==2);


}
/*int main()
{
	char **contact;
	clrscr();
	newContact(contact);
	clrscr();
	printf("name : %s phone: %s address: %s",contact[0],contact[1],contact[2]);
	getch();

return 0;
} */

void rectborder(int x1,int y1,int x2, int y2)
{
  /*printing corners*/
  gotoxy(x2,y1);
  cprintf("%c",191);
  gotoxy(x1,y2+1);
  cprintf("%c",192);
  gotoxy(x2,y2+1);
  cprintf("%c",217);
  gotoxy(x1,y1);
  cprintf("%c",218);
  /* printing lines */
  //upper border
	hline(x1+1,x1+2,y1);
	cprintf("[x]");
	hline(x1+6,x1+10,y1);
	cprintf("contact");
	hline(x1+18,x2-1,y1);
  //hline(x1+1,x2-1,y1);
  hline(x1+1,x2-1,y2+1);
  vline(y1+1,y2,x1);
  vline(y1+1,y2,x2);
}
void hline(int x1,int x2,int y)
{
  int i;
  for(i=x1;i<=x2;i++)
  {
	gotoxy(i,y);
	cprintf("%c",196);
  }
}
void vline(int y1,int y2,int x)
{
  int i;
  for(i=y1;i<=y2;i++)
  {
	gotoxy(x,i);
	cprintf("%c",179);
  }
}

