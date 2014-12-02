#include<stdio.h>
#include<conio.h>
#include<GRAPHICS.h>
#include<CTYPE.h>

#define HIGHLIGHT 0x30
#define NORMAL 0x07

#define RIGHT 77
#define LEFT  75
#define ENTER 13
#define HOME  71
#define END   79
#define ESC   27
#define UP    72
#define DOWN  80
#define BACKSPACE 8
#define tab 9

//#define startY 5
//#define startX 1

int pressedEsc=0;
//int length=0;

void makeMessageBox(int firstX,int firstY,int lastx , int lasty)
{
	int i,j;
	for(j=firstY;j<lasty;j++)
	{
		for(i=firstX;i<lastx;i++)
		{
			gotoxy(i,j);
			textattr(HIGHLIGHT);
			cprintf(" ");
		}
	}
}

void deleteMeessageBox(int firstx,int firsty,int lastx,int lasty,char * data)
{
	int i,j;
	int index=0;
	for(j=firsty;j<lasty+firsty;j++)
	{
		for(i=firstx;i<lastx+firstx;i++)
		{
			gotoxy(i,j);
			textattr(0x0F);
			cprintf(" ");
		}
	}
	gotoxy(firstx,firsty);
	textattr(0x0f);
	cprintf("%s",data);
}

void goToBegin(int firstX,int firstY)
{
	gotoxy(firstX,firstY);
}

void goToEnd(x,y)
{
	gotoxy(x,y);
}

void goToBeginLine(int line)
{
	gotoxy(1,line);
}

void goCursor(int index,int lineLength,int firstX,int firstY)
{
	int lines=(index/lineLength)+firstY;
	int last_line=index%lineLength;
	if(last_line==0)
	{
		lines-=1;
		last_line=lineLength;
	}
	gotoxy(last_line+firstX-1,lines);
}

char* run_textbox(int firstx,int firsty, int x,int y)
{
   //	char *tab="&!@#$tab";
  //	pressedEsc=0;
	char *current;
	char *first;
	char *last;
	int current_index;
	int first_index;
	int last_index;

	char *value;
	int len;
	int length=0;

	int i;
	char entered_char;

	int temp1;
	int temp2;
	int temp;

	pressedEsc=0;
	textattr(NORMAL);
	//clrscr();


	makeMessageBox(firstx,firsty,x+firstx,y+firsty);
   //	goToBegin();
	goCursor(1,x,firstx,firsty);

	//max index= x*y

	len=x*y;
	value=(char*)malloc(len*sizeof(char));


	//initialization
	first=current=last=value;
	first_index=current_index=last_index=1;

   //	getch();

	while(1)
	{
			entered_char=getch();
		   //	gotoxy(current_index-1,ROW);
			switch(entered_char)
			{
				case ESC:
					pressedEsc=1;
					return "STOP";
					break;
				case ENTER:
					textattr(NORMAL);
					/*
					clrscr();

					for(i=0;i<length;i++)
					{
						if(i%x==0 && i!=0)
							printf("\n");
						printf("%c",value[i]);
					}
					getch();
					*/
					if(value)
					{
						value[length]='\0';
						return value;
					}
					break;
				case tab:
					textattr(NORMAL);
					/*
					clrscr();

					for(i=0;i<length;i++)
					{
						if(i%x==0 && i!=0)
							printf("\n");
						printf("%c",value[i]);
					}
					getch();*/
					if(value)
					{
						value[length]='\0';
						return value;
					}
					/*
				case BACKSPACE:
							*(current-1)=' ';
							current--;
							last--;
							current_index--;
							last_index--;
							goCursor(current_index,x);
							printf("%c",*current);
							break;
							*/
						break;
				case NULL:
					entered_char=getch();
					switch(entered_char)
					{

						case UP:
						if(current_index!=len)
						{
							//not in first line
							if(current_index/x!=0)
							{
								temp=current_index-x;
								if(temp<=length)
								{
									temp1=current_index%x;
									temp2=(current_index/x)+firsty-1;
									if(temp1==0)
									{
										temp1=x;
										temp2-=1;
									}
									gotoxy(temp1+firstx-1 ,temp2);
									current_index-=x;
									current-=x;
								 }
							}
						}
							break;
						case DOWN:
						if(current_index!=len)
						{
							if(current_index/x!=(y-1))
							{
								temp=current_index+x;
								if(temp<=length)
								{
									temp1=current_index%x;
									temp2=(current_index/x)+1+firsty;
									if(temp1==0)
									{
										temp1=x;
										temp2-=1;
									}
									gotoxy(temp1+firstx-1,temp2);
									current_index+=x;
									current+=x;
								}
							}
						}
							break;
						case LEFT:
							if(current_index!=first_index)
							{
								if(current_index!=0)
								{
									current_index--;
									current--;
								   //	gotoxy(current_index);
								   goCursor(current_index,x,firstx,firsty);
								}
							  /*	else
								{
									 gotoxy(21,8);
									 printf("Begin of Line!!");
									 goToBegin();
								} */
							}
							break;
						case RIGHT:
							if(current_index!=last_index)
							{
								if(current_index!=len)
								{
									current_index++;
									current++;
									//gotoxy(current_index);
									goCursor(current_index,x,firstx,firsty);
								}
							}
							break;
						case HOME:
							//temp=*current;
							current=first;
							current_index=first_index;
							//printf("%c",temp);
							goToBegin(firstx,firsty);
							break;
						case END:
							current=last;
							current_index=last_index;
							//gotoxy(last_index);
							//goCursor(last_index,x);
							temp1=last_index%x;
							temp2=(last_index/x)+1;
							if(temp1==0)
							{
								temp2-=1;
								temp1=x;
							}
							gotoxy(temp1,temp2);
							break;
					}
					break;
			   default:
				  if(isprint(entered_char))
				  {
					 if(current_index==last_index)
					 {
						if(current_index!=len )
						{
							printf("%c",entered_char);
							*current=entered_char;
							current++;
							last++;
							current_index++;
							last_index++;
							length++;
							if(length>=x)
								goCursor(current_index,x,firstx,firsty);
						}
					 }
					 else
					 {
						printf("%c",entered_char);
						*current=entered_char;
						current++;
						current_index++;
						if(length>=x)
								goCursor(current_index,x,firstx,firsty);
					 }
				 }
			}
	}

	return value;
}


char* run_textbox_with_initial(int firstx,int firsty, int x,int y,char *initial)
{
   //	char *tab="&!@#$tab";
  //	pressedEsc=0;
	char *current;
	char *first;
	char *last;
	int current_index;
	int first_index;
	int last_index;

	char *value;
	int len;

	int length=0;
	int i;
	char entered_char;

	int temp1;
	int temp2;
	int temp;

	pressedEsc=0;
	textattr(NORMAL);
	//clrscr();

	length+=strlen(initial);


	makeMessageBox(firstx,firsty,x+firstx,y+firsty);
   //	goToBegin();
	goCursor(1,x,firstx,firsty);

	//max index= x*y

	len=x*y;
	value=(char*)malloc(len*sizeof(char));


	//initialization
	first=current=last=value;
	first_index=current_index=last_index=1;

	for(i=0;i<strlen(initial);i++)
	{	
		*current=initial[i];
		current++;
		last++;
		current_index++;
		last_index++;
		printf("%c",initial[i]);
	}

   //	getch();

	while(1)
	{
			entered_char=getch();
		   //	gotoxy(current_index-1,ROW);
			switch(entered_char)
			{
				case ESC:
					pressedEsc=1;
					return "STOP";
					break;
				case ENTER:
					textattr(NORMAL);
					/*
					clrscr();

					for(i=0;i<length;i++)
					{
						if(i%x==0 && i!=0)
							printf("\n");
						printf("%c",value[i]);
					}
					getch();
					*/
					if(value)
					{
						value[length]='\0';
						return value;
					}
					break;
				case tab:
					textattr(NORMAL);
					/*
					clrscr();

					for(i=0;i<length;i++)
					{
						if(i%x==0 && i!=0)
							printf("\n");
						printf("%c",value[i]);
					}
					getch();*/
					if(value)
					{
						value[length]='\0';
						return value;
					}
					/*
				case BACKSPACE:
							*(current-1)=' ';
							current--;
							last--;
							current_index--;
							last_index--;
							goCursor(current_index,x);
							printf("%c",*current);
							break;
							*/
						break;
				case NULL:
					entered_char=getch();
					switch(entered_char)
					{

						case UP:
						if(current_index!=len)
						{
							//not in first line
							if(current_index/x!=0)
							{
								temp=current_index-x;
								if(temp<=length)
								{
									temp1=current_index%x;
									temp2=(current_index/x)+firsty-1;
									if(temp1==0)
									{
										temp1=x;
										temp2-=1;
									}
									gotoxy(temp1+firstx-1 ,temp2);
									current_index-=x;
									current-=x;
								 }
							}
						}
							break;
						case DOWN:
						if(current_index!=len)
						{
							if(current_index/x!=(y-1))
							{
								temp=current_index+x;
								if(temp<=length)
								{
									temp1=current_index%x;
									temp2=(current_index/x)+1+firsty;
									if(temp1==0)
									{
										temp1=x;
										temp2-=1;
									}
									gotoxy(temp1+firstx-1,temp2);
									current_index+=x;
									current+=x;
								}
							}
						}
							break;
						case LEFT:
							if(current_index!=first_index)
							{
								if(current_index!=0)
								{
									current_index--;
									current--;
								   //	gotoxy(current_index);
								   goCursor(current_index,x,firstx,firsty);
								}
							  /*	else
								{
									 gotoxy(21,8);
									 printf("Begin of Line!!");
									 goToBegin();
								} */
							}
							break;
						case RIGHT:
							if(current_index!=last_index)
							{
								if(current_index!=len)
								{
									current_index++;
									current++;
									//gotoxy(current_index);
									goCursor(current_index,x,firstx,firsty);
								}
							}
							break;
						case HOME:
							//temp=*current;
							current=first;
							current_index=first_index;
							//printf("%c",temp);
							goToBegin(firstx,firsty);
							break;
						case END:
							current=last;
							current_index=last_index;
							//gotoxy(last_index);
							//goCursor(last_index,x);
							temp1=last_index%x;
							temp2=(last_index/x)+1;
							if(temp1==0)
							{
								temp2-=1;
								temp1=x;
							}
							gotoxy(temp1,temp2);
							break;
					}
					break;
			   default:
				  if(isprint(entered_char))
				  {
					 if(current_index==last_index)
					 {
						if(current_index!=len )
						{
							printf("%c",entered_char);
							*current=entered_char;
							current++;
							last++;
							current_index++;
							last_index++;
							length++;
							if(length>=x)
								goCursor(current_index,x,firstx,firsty);
						}
					 }
					 else
					 {
						printf("%c",entered_char);
						*current=entered_char;
						current++;
						current_index++;
						if(length>=x)
								goCursor(current_index,x,firstx,firsty);
					 }
				 }
			}
	}

	return value;
}

/*
int main(void)
{

	int startx,starty,numOfChars,numOfLines;
	char *result;


	clrscr();
	printf("enter the line you want to start from : ");
	scanf("%d",&startx);

	printf("enter the row you want to start from : ");
	scanf("%d",&starty);

	printf("enter number of character per line : ");
	scanf("%d",&numOfChars);

	printf("enter number of lines : ");
	scanf("%d",&numOfLines);



	result=run_textbox(startx,starty,numOfChars,numOfLines);
} */