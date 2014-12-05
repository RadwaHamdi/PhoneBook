# include <stdio.h>
# include <conio.h>

# include <dos.h>
# include "hossam.h"
#include "LAYOUT.h"
//#include "hossamtextbox	.h"
//#include "FILE.h"

/* ..ASCII and Scan Codes of Keys.. */
#define highlight 0xf0
#define normal 0x07
# define ESC 27
# define ENTER 13
# define RIGHT 77
# define LEFT 75
# define HOME 71
# define END 79
# define INSERT 82
# define DEL 83
#define tab 9
#define enter 13

#define enter 13
#define esc 27
#define up  72
#define down 80
#define home 71
#define end 79
#define tab 9
#define pageup 73
#define pagedown 81
#define highlight 0x70
#define normal 0x10
#define back 8
void rectborder(int,int,int,int,char *);
void hline(int,int,int);
void vline(int,int,int);
int nextBtn(struct phonebook* ,char* ,char* ,char* ,int);
int deleteBtn(struct phonebook* ,char* ,char* ,char* ,int);
int editBtn(struct phonebook* ,char* ,char* ,char* ,int);
void viewsearchresult(struct phonebook*);
void notfoundsearch(int);

union REGS in_regs, out_regs;

void detectmouse (void)
{

	in_regs.x.ax = 0;
	int86 (0X33,&in_regs,&out_regs);
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

/*-   ..Checks the status of Insert Key..   ..Returns..   ..1 if ON..   ..0 if OFF..--*/
int ins_state ( void )
{
  unsigned char far *stat =(char far*)0x417 ;

  char status ;

  status = *stat ;

  if ( ( status & 128 ) == 128 )
	 return 1;
  else return 0;
}

/*---    ..Changes the shape of cursor..--------*/
void cursor_shape ( int y , int x )
{
	union REGS i, o ;
	i.h.ah = 1 ;
	i.h.ch = y ;
	i.h.cl = x ;
	int86 ( 16, &i, &o ) ;
}

/*-------..Restores the screen to the orginal state..-------------*/
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

/*----    ..Function for drawing horizontal line..-------------*/
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

/*------  ..The important fuction.---- Available Keys -----+|    ~ Right Arrow --> For moving the cursor to the right                 ||    ~ Left  Arrow --> For moving the cursor to the left                  ||    ~ DEL         --> For deleting characters                            ||    ~ Backspace   --> For deleting characters                            ||    ~ Insert      --> For inserting charcters                            ||    ~ Home           --> For going to the beginning of the text             ||    ~ End         --> For going to the end of the text                   ||    ~ ESC           --> For clearing the textbox---------+*/
char * txtbox ( int length )
{
   char str[80];  /*              ..Array into which characters are being stored,               the length of the string is limited to 80..             ..Just change the length to meet your needs..             ..You can even use dynamic memory allocation, if you               are poor in memory..          */
   char key;

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

/*I have used the colors -------------*/

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

	  /* ..For storing the typed characters into the array.. */
	  if ( key > 31 && key < 127 && x < ( startx + length ) )
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
void button(int x1,int y1,char * btxt,int selected)  // 0 not selected 1 selected
{
	gotoxy(x1,y1);
	if(selected==0)
	textbackground(0x43);
	else
	textbackground(YELLOW);
	fillrect(x1,y1,x1+8,y1);
	gotoxy(x1+1,y1);
	textcolor(BLACK);
	cprintf("%s",btxt);
}

int messageboxnew(int x1,int y1,int x2,int y2)
{
	char name[]="";
	char tele[]="";
	char address[]="";
	int index=3;
	char ch;//radwa
	textbackground(BLACK);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Contact");
	textbackground(BLUE);
	fillrect(x1+2,y1+2,x2-1,y2-1);

	button(x1+3,y2-1,"DONE",0);
	button(x1+12,y2-1,"CANCEL",1);
	
	if(index ==1) return 1;
	//button(x1+21,y2-1,"NEXT");
	gotoxy(x1+2,y1+2);
	textbackground(0x43);
	textcolor(BLACK);
	cprintf("Name         Telephone   Address\n");
	gotoxy(x1+2,y1+4);
	textcolor(BLACK);
	textbackground(BLUE);
	cprintf("%s  %s   %s",name,tele,address);
	gotoxy(x1+4,y2-1);
	return index;
}
void messageboxsearch(int x1,int y1,int x2,int y2,char * name,char *tele ,char *address)
{
	//char ch;//radwa code
	textbackground(BLACK);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Contact");
	textbackground(BLUE);
	fillrect(x1+2,y1+2,x2-1,y2-1);

	button(x1+3,y2-1,"DELETE",1);
	button(x1+12,y2-1,"EDIT",0);
	button(x1+21,y2-1,"NEXT",0);
	gotoxy(x1+2,y1+2);
	textbackground(0x43);
	textcolor(BLACK);
	cprintf("Name         Telephone   Address\n");
	gotoxy(x1+2,y1+4);
	textcolor(BLACK);
	textbackground(BLUE);
	//cprintf("%s  %s   %s",name,tele,address);
   //radwa code	//ch=getch();
	gotoxy(x1+4,y2-1);
}
void messageboxedit(int x1,int y1,int x2,int y2,char * name,char *tele ,char *address)
{

	textbackground(BLACK);
	   //	fillrect(0,0,80,30);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Contact");
	textbackground(BLUE);
	fillrect(x1+2,y1+2,x2-1,y2-1);

	button(x1+3,y2-1,"DELETE",0/*radwa code*/);
	//button(x1+12,y2-1,"DONE");
	button(x1+21,y2-1,"DONE",0/*radwa code*/);
	gotoxy(x1+2,y1+2);
	textbackground(0x43);
	textcolor(BLACK);
	cprintf("Name         Telephone   Address\n");
	gotoxy(x1+2,y1+4);
	textcolor(BLACK);
	textbackground(BLUE);
	cprintf("%s  %s   %s",name,tele,address);
	gotoxy(x1+4,y2-1);
}
/*------- showed boxes--------*/
void notfoundsearch(int field)
{
	int x1=6, y1=8, x2=40, y2=15;
	char fields[3][10]={"name","phone","address"};
	textbackground(BLACK);
       //	fillrect(0,0,80,30);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Not Found");

	gotoxy(x1+3,y1+3);
	cprintf("Can not found this %s ",fields[field]);

	//button(x1+3,y2-1,"DELETE");
	button(x1+12,y2-1,"OK",0);
	//button(x1+21,y2-1,"Cancel");
	gotoxy(x1+2,y1+2);
	textbackground(0x43);

	gotoxy(x1+4,y2-1);
	getch();
}
void deleteConfirmMessage()
{
	int x1=6, y1=8, x2=40, y2=15;
	int pos=0,i,j,n,k,index=0,b=0;
	char key;
	char nam[80];
	int terminate=0;
	int selected=0;
	int x=4,y=10,size;
	char btn[2][10]={"DELETE","CANCEL"};
	textbackground(BLACK);

	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Warning");

	gotoxy(x1+3,y1+3);
	cprintf("Are you sure you want to");
	gotoxy(x1+4,y1+4);
	cprintf("delete this file?");

       //	button(x1+3,y2-1,"DELETE",0);
	//button(x1+12,y2-1,"DONE");
       //	button(x1+21,y2-1,"Cancel",0);
	gotoxy(x1+2,y1+2);
	textbackground(0x43);

	gotoxy(x1+4,y2-1);

	/*****/
	do
	{
		//draw menu with highlight item
		for(i=0;i<2;i++)
		{
			if(i==pos)
			  selected=1;
			button(x1+3+21*i,y2-1,btn[i],selected);
			    //	textattr(0x10);
		       //	gotoxy(x1+3+21*i,y2-1);
		       //	cprintf("%s",btn[i]);
			selected=0;
			       //	textattr(0x43);
		}
		flushall();
		key=getch();
		switch(key)
		{
			case '\0':
				key=getch();
				switch(key)
				{
					case LEFT:
						pos--;
						if(pos<0)pos=1;
						break;
					case RIGHT:
						pos++;
						if(pos>1)pos=0;
						break;
					case home:
						pos=0;
						break;
					case end:
						pos=1;
						break;
					case pageup:
						pos--;
						if(pos<0)pos=1;
						break;
					case pagedown:
						pos++;
						if(pos>1)pos=0;
						break;
				}
				break;
			case enter:
				switch(pos)
				{
					case 0:
						break;
					case 1:
						terminate=1;
						break;
				}
				break;
			case tab:
				pos++;
				if(pos>1)pos=0;
				break;
			case esc:
				terminate=1;
				break;
		}
	}while(terminate!=1);
	clrscr();
	background_color(0x00);
	draw_border_shortcut(1,25);
	draw_content();
	display_all();
}
int deleteRecordMessage()//return 1 for delete return 0 for cancel
{
	struct phonebook *temp;
	int x1=6, y1=8, x2=40, y2=15;
	int pos=0,ii,j,n,k,index=0,b=0;
	char key;
	char nam[80];
	int terminate=0;
	int selected=0;
	int x=4,y=10,del;
	char btn[2][10]={"DELETE","CANCEL"};
	textbackground(BLACK);

	temp=get_element_by_index(i);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Warning");

	gotoxy(x1+3,y1+3);
	cprintf("Are you sure you want to");
	gotoxy(x1+4,y1+4);
	cprintf("delete %s contact?",temp->name);

	gotoxy(x1+2,y1+2);
	textbackground(0x43);

	gotoxy(x1+4,y2-1);

	/*****/
	do
	{
		//draw menu with highlight item
		for(ii=0;ii<2;ii++)
		{
			if(ii==pos)
			  selected=1;
			button(x1+3+21*ii,y2-1,btn[ii],selected);
			selected=0;
		
		}
		flushall();
		key=getch();
		switch(key)
		{
			case '\0':
				key=getch();
				switch(key)
				{
					case LEFT:
						pos--;
						if(pos<0)pos=1;
						break;
					case RIGHT:
						pos++;
						if(pos>1)pos=0;
						break;
					case home:
						pos=0;
						break;
					case end:
						pos=1;
						break;
					case pageup:
						pos--;
						if(pos<0)pos=1;
						break;
					case pagedown:
						pos++;
						if(pos>1)pos=0;
						break;
				}
				break;
			case enter:
				switch(pos)
				{
					case 0:
						delete_node(temp->name);
						del=1;
						terminate=1;
						break;
					case 1:
						del=0;
						terminate=1;
						break;
				}
				break;
			case tab:
				pos++;
				if(pos>1)pos=0;
				break;
			case esc:
				terminate=1;
				break;
		}
	}while(terminate!=1);
	clrscr();
	background_color(0x00);
	draw_border_shortcut(1,25);
	draw_content();
	display_all();
	return del;
}
int saveBeforeClose()// return 0 for yes , 1 for no ,2 for cancel
{
	int x1=6, y1=8, x2=40, y2=15;
	int pos=0,i,j,n,k,index=0,b=0;
	char key;
	char nam[80];
	int terminate=0;
	int selected=0;
	int x=4,y=10,save;
	char btn[3][10]={"YES","NO","CANCEL"};
	textbackground(BLACK);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Warning");

	gotoxy(x1+3,y1+3);
	cprintf("Do you want to save changes");
	gotoxy(x1+4,y1+4);
	cprintf("before closing this program?");

	gotoxy(x1+2,y1+2);

	gotoxy(x1+4,y2-1);
	/********/
	do
	{
		//draw menu with highlight item
		for(i=0;i<3;i++)
		{
			if(i==pos)
			  selected=1;
			button(x1+3+9*i,y2-1,btn[i],selected);
				selected=0;
		}
		flushall();
		key=getch();
		switch(key)
		{
			case '\0':
				key=getch();
				switch(key)
				{
					case LEFT:
						pos--;
						if(pos<0)pos=2;
						break;
					case RIGHT:
						pos++;
						if(pos>2)pos=0;
						break;
					case home:
						pos=0;
						break;
					case end:
						pos=2;
						break;
					case pageup:
						pos--;
						if(pos<0)pos=2;
						break;
					case pagedown:
						pos++;
						if(pos>2)pos=0;
						break;
				}
				break;
			case enter:
				switch(pos)
				{
					case 0:
					 //save
						save=0;
						write_file(currentFile);
						break;
					case 1:
					  //no save
	
						terminate=1;
						exit(0);
						break;
					case 2:
					 //cancel
						terminate=1;
						break;
				}
				break;
			case tab:
				pos++;
				if(pos>2)pos=0;
				break;
			case esc:
				clrscr();
				background_color(0x00);
				draw_border_shortcut(1,25);
				draw_content();
				display_all();
				terminate=1;
				break;
		}
	}while(terminate!=1);
	clrscr();
	background_color(0x00);
	draw_border_shortcut(1,25);
	draw_content();
	display_all();
}



char * viewsearchbox(int index)
{
	char* key;
    char keys[3][15]={"Name is :","Phone is :", "Address is :"};
	int x1=5, y1=7, x2=40, y2=15;
	char buffer [4096],key2,ch,ch2;
	int terminate=0,loap;
	struct phonebook * temp;
	gettext(1,1,80,25,buffer);
	textbackground(BLACK);
 
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);

	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"Search");
	gotoxy(x1+3,y1+3);
	cprintf(" %s ",keys[index]);
	//button(x1+12,y2-1,"Search",0);
	button(x1+8,y2-2,"Search",0);
	button(x1+18,y2-2,"Cancel",0);
	
	do
	{
		do
		{
			if(terminate!=4) key=run_textbox(x1+14,y1+3,15,1);
			else			 key=run_textbox_with_initial(x1+14,y1+3,15,1,key);
		}while(key && key[0]=='\0' || (is_spaces(key)) || ((index==1 && !(is_phone(key)))  && (strcmp(key,"STOP")!=0)) );

	//button(x1+21,y2-1,"NEXT");
	//gotoxy(x1+2,y1+2);
		if(pressedEsc == 1) break;
	do
	{

		button(x1+8,y2-2,"Search",1);
		button(x1+18,y2-2,"CANCEL",0);
		gotoxy(x1+9,y2-2);   // hena kda hayroo7 3nd Done
		ch=getch();
		switch(ch)
		{
			case NULL:
				ch=getch();
				switch(ch)
				{
				// to left button "cancel"
				
					case RIGHT:
						button(x1+8,y2-2,"Search",0);
						button(x1+18,y2-2,"CANCEL",1);
						gotoxy(x1+19,y2-2);
						ch2=getch();
							switch(ch2)
							{
								case NULL:
									ch=getch();
									switch(ch)
										{
										case RIGHT:
										case LEFT:
											terminate=3;
											break;
										}
								break;
								case ENTER:
									terminate=1;
								break;
								case tab:
									terminate=4;//back to text
									break;
								
							}
						break;	
				}
			break;
			case tab:
				button(x1+8,y2-2,"Search",0);
				button(x1+18,y2-2,"CANCEL",1);
				gotoxy(x1+19,y2-2);
				ch2=getch();
					switch(ch2)
					{
						case NULL:
							ch=getch();
							switch(ch)
								{
								case RIGHT:
								case LEFT:
									terminate=3;
									break;
								}
							break;
						case ENTER:
							terminate=1;
							break;
						case tab:
							terminate=4;//back to text
							break;
					}
				break;	
			case ENTER:
				temp=search(key,index+1);
				//printf("defwfffffffffffffffffffff");
				if(lengthOfArray == 0)
						notfoundsearch(index);
				else
					{
					//commented till change viewsearchresult  parameters
						 viewsearchresult(temp);
						//viewsearchresult(temp);
					}
				terminate=1;
				break;
		}
		
	}while(terminate==3);
	}while(terminate==4);
	
	
	
	puttext(1,1,80,25,buffer);
	
	
	return key;
}

 void newContact(void)
{
	char *temp_name;
	char *temp_phone;
	char *temp_address;
	int terminate=0;
	int x=7,y=11;
	char ch,ch2;
	int flag=0;
	messageboxnew(5,7,40,15);
	detectmouse();
	showmousetext();
	  
  do
  {
  	x=7;
  	y=11;
  	gotoxy(x,y);
  	flushall();
  	if(flag==0)
  	{
	  	do
	  	{
	  		temp_name=run_textbox(x,y,10,1);
	  	}while(temp_name && temp_name[0] == '\0' || (is_spaces(temp_name)));
		//deleteMeess			ageBox(x,y,10,1,temp_name);
		if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
		x+=11;
		gotoxy(x,y);
		flushall();
		
		do
		{
			temp_phone=run_textbox(x,y,11,1);
		}while(temp_phone && temp_phone[0] == '\0' || (is_spaces(temp_phone)) || (!(is_phone(temp_phone))) && (strcmp(temp_phone,"STOP")!=0 ) );
		//deleteMeessageBox(x,y,11,1,temp_phone);
		if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
		x+=12	;
		gotoxy(x,y);
		flushall();
		
		do
		{
	    	temp_address=run_textbox(x,y,7,1);
	    }while(temp_address && temp_address[0] == '\0' || (is_spaces(temp_address)));
		//deleteMeessageBox(x,y,7,1,temp_address);
		if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
	}
	else
	{
		do
	  	{
	  		temp_name=run_textbox_with_initial(x,y,10,1,temp_name);
	  	}while(temp_name && temp_name[0] == '\0' || (is_spaces(temp_name)));
		//deleteMeess			ageBox(x,y,10,1,temp_name);
		if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
		x+=11;
		gotoxy(x,y);
		flushall();
		
		do
		{
			temp_phone=run_textbox_with_initial(x,y,11,1,temp_phone);
		}while(temp_phone && temp_phone[0] == '\0' || (is_spaces(temp_phone)) || (!(is_phone(temp_phone))) && (strcmp(temp_phone,"STOP")!=0 ) );
		//deleteMeessageBox(x,y,11,1,temp_phone);
		if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
		x+=12	;
		gotoxy(x,y);
		flushall();
		
		do
		{
	    	temp_address=run_textbox_with_initial(x,y,7,1,temp_address);
	    }while(temp_address && temp_address[0] == '\0' || (is_spaces(temp_address)));
		//deleteMeessageBox(x,y,7,1,temp_address);
		if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}

	}
	do
	{
		terminate=3;
		button(8,14,"DONE",1);
		button(17,14,"CANCEL",0);
		gotoxy(9,14);
		ch=getch();
		switch(ch)
		{
			case NULL:
				ch=getch();
				switch(ch)
				{
					case RIGHT:
						button(8,14,"DONE",0);
						button(17,14,"CANCEL",1);
						gotoxy(17,14);
						ch2=getch();
							switch(ch2)
							{
								case NULL:
									ch=getch();
									switch(ch)
										{
										case LEFT:
											terminate=3;
											break;
									}
									break;
								case ENTER:
									terminate=1;
									break;
								case tab:
									terminate=2;
									break;
								default:
									terminate=3;
									break;
							}
						break;	
					}
					break;
			case tab:
				button(8,14,"DONE",0);
				button(17,14,"CANCEL",1);
				gotoxy(17,14);
				ch2=getch();
				switch(ch2)
				{
					case NULL:
						ch=getch();
						switch(ch)
						{
							case LEFT:
								terminate=3;
								break;
						}
						break;
					case ENTER:
						terminate=1;
						break;
					case tab:
						terminate=2;
						break;
				}
				break;
			case ENTER:
				if(temp_name !="" || temp_name!=" " || temp_phone!="" || temp_phone!=" " || temp_address!="" ||temp_address!=" ")
					create_add_node(temp_name,temp_phone,temp_address);
				terminate=1;
				break;
			default:
				terminate=3;
				break;
		}
	}while(terminate==3);
	flag++;
}while(terminate==2);
	   clrscr();
		background_color(0x00);
		draw_border_shortcut(1,25);
		draw_content();
	   display_all();
}



int deleteBtn(struct phonebook* temp,char* temp_name,char* temp_phone,char* temp_address,int ii)
{
	char ch;
	button(8,14,"DELETE",1);
	button(17,14,"EDIT",0);
	button(26,14,"NEXT",0);
	gotoxy(9,14);
	ch=getch();
	switch(ch)
	{
		case tab:
			return editBtn(temp,temp_name,temp_phone,temp_address,ii);
			break;
		case ENTER:
			delete_node(temp->name);
			return 1;
			break;
		case NULL:
			ch=getch();
			switch(ch)
			{
				case LEFT:
					return nextBtn(temp,temp_name,temp_phone,temp_address,ii);
					break;
				case RIGHT:
					return editBtn(temp,temp_name,temp_phone,temp_address,ii);
					break;
				default:
					return 2;
					break;
			}
			break;
		default:
			return 2;
			break;	
	}
	return 2;
}

int editBtn(struct phonebook* temp,char* temp_name,char* temp_phone,char* temp_address,int ii)
{
	char ch;
	button(8,14,"DELETE",0);
	button(17,14,"EDIT",1);
	button(26,14,"NEXT",0);
	gotoxy(17,14);
	ch=getch();
	switch(ch)
	{
		case tab:
			return nextBtn(temp,temp_name,temp_phone,temp_address,ii);
			//break;
		case ENTER:
			delete_node(temp->name);
			create_add_node(temp_name,temp_phone,temp_address);
			return 1;
		    //break;
		case NULL:
			ch=getch();
			switch(ch)
			{
				case LEFT:
					return deleteBtn(temp,temp_name,temp_phone,temp_address,ii);
					//break;
				case RIGHT:
					return nextBtn(temp,temp_name,temp_phone,temp_address,ii);
					//break;
				default:
					return 2;
					break;
			}
			//break;
		default:
			return 2;
			break;
	}
	return 2;
}

int nextBtn(struct phonebook* temp,char* temp_name,char* temp_phone,char* temp_address,int ii)
{
	char ch;
	struct phonebook * temp2;
	button(8,14,"DELETE",0);
	button(17,14,"EDIT",0);
	button(26,14,"NEXT",1);
	gotoxy(26,14);
	ch=getch();
	switch(ch)
	{
		case tab:
			return 2;
			//break;

		case ENTER:
				if(!(ii+1<lengthOfArray))
				{
					return nextBtn(temp,temp_name,temp_phone,temp_address,ii);
				}
				if(ii+1<lengthOfArray)
				{
					ii+=1;
					clrscr();
					background_color(0x00);
					draw_border_shortcut(1,25);
					draw_content();
					display_all();
					temp++;
					viewsearchresult(temp);
				}
			  return 1;

		case NULL:
			ch=getch();
			switch(ch)
			{
				case LEFT:
					return editBtn(temp,temp_name,temp_phone,temp_address,ii);
					//break;
				case RIGHT:
					return deleteBtn(temp,temp_name,temp_phone,temp_address,ii);
					//break;
				default:
					return 2;
					break;
			}
			//break;
		default:
			return 2;
			break;
	}
	return 2;
}



void viewsearchresult(struct phonebook *temp)
{
	char *temp_name;
	char *temp_phone;
	char *temp_address;
	int terminate=0;
	int x=7,y=11;
	char ch,ch2;
	int flag=0;

	messageboxsearch(5,7,40,15,temp->name,temp->phone,temp->address);
	detectmouse();
	showmousetext();
	  
  do
  {
  	if(flag==0)
		{
			
			gotoxy(7,11);
			printf(temp->name);
			gotoxy(7+12,11);
			printf(temp->phone);
			gotoxy(7+12+12,11);
			printf(temp->address);
			
			x=7;
			y=11;
			gotoxy(x,y);
			do
			{	
				temp_name=run_textbox_with_initial(x,y,10,1,temp->name);
			}while(temp_name&&temp_name[0]=='\0' || (is_spaces(temp_name)));
			if(pressedEsc == 1)
			{
				terminate=1;
				break;
			}
			x+=12;
			gotoxy(x,y);
			do
			{	
				temp_phone=run_textbox_with_initial(x,y,11,1,temp->phone);
			}while(temp_phone && temp_phone[0]=='\0' || (is_spaces(temp_phone)) || (!(is_phone(temp_phone))) && (strcmp(temp_phone,"STOP")!=0 ) );
			if(pressedEsc == 1)
			{
				terminate=1;
				break;
			}
			x+=12;
			gotoxy(x,y);
			do
			{
				temp_address=run_textbox_with_initial(x,y,7,1,temp->address);
			}while(temp_address && temp_address[0] == '\0' || (is_spaces(temp_address)));
			if(pressedEsc == 1)
			{
				terminate=1;
				break;
			}
		}
	else
		{
			x=7;
			y=11;
				gotoxy(x,y);
			do
			{	
				temp_name=run_textbox_with_initial(x,y,10,1,temp_name);
			}while(temp_name&&temp_name[0]=='\0' || (is_spaces(temp_name)));
			if(pressedEsc == 1)
			{
				terminate=1;
				break;
			}
			x+=12;
			gotoxy(x,y);
			do
			{	
				temp_phone=run_textbox_with_initial(x,y,11,1,temp_phone);
			}while(temp_phone && temp_phone[0]=='\0' || (is_spaces(temp_phone)) || (!(is_phone(temp_phone))) && (strcmp(temp_phone,"STOP")!=0 ) );
			if(pressedEsc == 1)
			{
				terminate=1;
				break;
			}
			x+=12;
			gotoxy(x,y);
			do
			{
				temp_address=run_textbox_with_initial(x,y,7,1,temp_address);
			}while(temp_name && temp_name[0] == '\0' || (is_spaces(temp_address)));
			if(pressedEsc == 1)
			{
				terminate=1;
				break;
			}
		}

		terminate=deleteBtn(temp,temp_name,temp_phone,temp_address,0);
		flag++;
  }while(terminate==2);
	   clrscr();
		background_color(0x00);
		draw_border_shortcut(1,25);
		draw_content();
	    display_all();
}

void showeditbox(char * name,char *tele ,char *address)
{
	char ch;
	char ch2;
	struct phonebook *temp;
	int flag=0;
	char *temp_name;
	char *temp_phone;
	char *temp_address;
	int terminate=0;
	int x;
	int y;
	temp=get_element_by_index(i);
	messageboxedit(5,7,40,15, name,tele ,address);
	do
	{
		if(flag==0)
		{
			gotoxy(7,11);
			printf(temp->name);
			gotoxy(7+11,11);
			printf(temp->phone);
			gotoxy(7+11+12,11);
			printf(temp->address);

			x=7;
			y=11;
			gotoxy(x,y);
			do
			{	
				temp_name=run_textbox_with_initial(x,y,10,1,temp->name);
			}while(temp_name&&temp_name[0]=='\0' || (is_spaces(temp_name)));
			if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
			x+=11;
			gotoxy(x,y);
			do
			{	
				temp_phone=run_textbox_with_initial(x,y,11,1,temp->phone);
			}while(temp_phone && temp_phone[0]=='\0' || (is_spaces(temp_phone)) || (!(is_phone(temp_phone))) && (strcmp(temp_phone,"STOP")!=0 ) );
			if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
			x+=12;
			gotoxy(x,y);
			do
			{
				temp_address=run_textbox_with_initial(x,y,7,1,temp->address);
			}while(temp_address && temp_address[0] == '\0' || (is_spaces(temp_address)));
			if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
		}
		else
		{
			x=7;
			y=11;
			gotoxy(x,y);
			do
			{	
				temp_name=run_textbox_with_initial(x,y,10,1,temp_name);
			}while(temp_name&&temp_name[0]=='\0' || (is_spaces(temp_name)));
			if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
			x+=11;
			gotoxy(x,y);
			do
			{	
				temp_phone=run_textbox_with_initial(x,y,11,1,temp_phone);
			}while(temp_phone && temp_phone[0]=='\0' || (is_spaces(temp_phone)) || (!(is_phone(temp_phone))) && (strcmp(temp_phone,"STOP")!=0 ) );
			if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
			x+=12;
			gotoxy(x,y);
			do
			{
				temp_address=run_textbox_with_initial(x,y,7,1,temp_address);
			}while(temp_name && temp_name[0] == '\0' || (is_spaces(temp_address)));
			if(pressedEsc == 1)
			{
				terminate=2;
				break;
			}
		}

		do
		{
			button(8,14,"DELETE",1);
			button(26,14,"DONE",0);
			gotoxy(9,14);
			ch=getch();
			switch(ch)
			{
				case NULL:
					ch=getch();
					switch(ch)
					{
						case RIGHT:
							button(8,14,"DELETE",0);
							button(26,14,"DONE",1);
							gotoxy(26,14);
							ch2=getch();
								switch(ch2)
								{
									case NULL:
										ch=getch();
										switch(ch)
											{
											case LEFT:
												terminate=3;
												break;
										}
										break;
									case ENTER:
										if(temp_name !="" || temp_name!=" " || temp_phone!="" || temp_phone!=" " || temp_address!="" ||temp_address!=" ")
											{
												delete_node(temp->name);
												create_add_node(temp_name,temp_phone,temp_address);
											}
										terminate=1;
										break;
									case tab:
										terminate=2;
										break;
									default:
										terminate=3;
										break;
								}
							break;	
						default:
							terminate=3;
							break;
						}
						break;
				case tab:
					button(8,14,"DELETE",0);
					button(26,14,"DONE",1);
					gotoxy(26,14);
					ch2=getch();
					switch(ch2)
					{
						case NULL:
							ch=getch();
							switch(ch)
							{
								case LEFT:
									terminate=3;
									break;
							}
							break;
						case ENTER:
							if(temp_name !="" || temp_name!=" " || temp_phone!="" || temp_phone!=" " || temp_address!="" ||temp_address!=" ")
								{
									delete_node(temp->name);
									create_add_node(temp_name,temp_phone,temp_address);
								}
							terminate=1;
							break;
						case tab:
							terminate=2;
							break;
						default:
							terminate=3;
							break;
					}
					break;
				case ENTER:
					delete_node(temp->name);
					terminate=1;
					break;
				default:
					terminate=3;
					break;
			}
		}while(terminate==3);
		flag++;
	}while(terminate==2);
	clrscr();
	background_color(0x00);
	draw_border_shortcut(1,25);
	draw_content();
	display_all();
}





char* createFileBox(void)
{
	char* fname;
	int x1=5, y1=7, x2=40, y2=15;
	char buffer [4096],ch;
	//struct phonebook * temp;
	gettext(1,1,80,25,buffer);
	 //big white box
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);

	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"New File");
	gotoxy(x1+3,y1+3);
	cprintf(" File Name :");
	button(x1+12,y2-1,"Create",0);

	gotoxy(x1+14,y1+3);
	textbackground(BLUE);
	fname=txtbox(15);
	//// when press enter the box dissappear and data return to its state
	ch=getch();
	if(ch==ENTER)
	   return fname;
	else if(ch==ESC)
	   return NULL;
	return fname;
}


void openfile(/*char* files,int size*/)
{
	int x1=6, y1=8, x2=35, y2=17;
	char files[4][10]={"phone1","phone2","phone3","phone4"};
	int pos=0,i,j,n,k,index=0,b=0;
	char key;
	char nam[80];
	int terminate=0;
	int x=4,y=10,size=4;
       //	clrscr();
       //	cprintf("%s",files[0]);
	textbackground(WHITE);
	fillrect(x1,y1,x2+1,y2+1);
	textcolor(BLACK);
	rectborder(x1+1,y1+1,x2-1,y2-1,"OpenFile");
	textbackground(BLUE);
	fillrect(x1+4,y1+2,x2-3,y2-1);
	fillrect(x1+4,y1+3,x2-3,y2-1);

	button(x1+12,y2-1,"Open",0);
	do
	{
		//draw menu with highlight item
		for(i=0;i<size;i++)
		{
			if(i==pos)
				textattr(highlight);
			gotoxy(x1+5,y1+2+1*i);
			cprintf("%s",files[i]);
			textattr(normal);
		}
		flushall();
		key=getch();
		switch(key)
		{
			case '\0':
				key=getch();
				switch(key)
				{
					case up:
						pos--;
						if(pos<0)pos=size-1;
						break;
					case down:
						pos++;
						if(pos>size-1)pos=0;
						break;
					case home:
						pos=0;
						break;
					case end:
						pos=size-1;
						break;
					case pageup:
						pos--;
						if(pos<0)pos=size-1;
						break;
					case pagedown:
						pos++;
						if(pos>size-1)pos=0;
						break;
				}
				break;
			case enter:
				switch(pos)
				{
					case 0:
					//open file1
										getch();
						break;
					case 1: //file2

						getch();
						break;
					case 2: //file3
						terminate=1;
						break;
					case 3:
						break;
					case 4:
						break;

				}
				break;
			case tab:
				pos++;
				if(pos>size-1)pos=0;
				break;
			case esc:
				terminate=1;
				break;

		}

	}while(terminate!=1);

}


/*int main()
{
  int x1,y1,x2,y2;
  int edit=0;
  char ch;
  clrscr();


  messagebox(5,7,40,15);
  detectmouse ();
  showmousetext ();
  getch();
  edit=1;
  if(edit)
  {
	gotoxy(7,11);
	txtbox(14);
	ch=getch();
   switch(ch)
   {
	case tab:
	gotoxy(7+14,11);
	txtbox(11);
	ch=getch();
	switch(ch)
	{
		case tab:
		gotoxy(7+14+12,11);
		txtbox(5);
		break;
	}
	break;

   }
  }
  getch();
  return 0;
}*/

void rectborder(int x1,int y1,int x2, int y2,char * message)
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
	cprintf(message);
	hline(x1+20,x2-1,y1);
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

