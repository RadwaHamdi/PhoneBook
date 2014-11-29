#include<stdio.h>
#include<conio.h>
#include <dos.h>
#include <graphics.h>

#define NORMAL 0x07
   /*
union REGS in, out;

void detectmouse ()
{

	in.x.ax = 0;
	int86 (0X33,&in,&out);
	/*
	if (out.x.ax == 0)
	printf ("\n Mouse Fail To Initialize");
	else
	printf ("\n Mouse Succesfully Initialize");
	*//*
}

void showmousetext ()
{

	in.x.ax = 1;
	int86 (0X33,&in,&out);
}*/
void background_color(int color)
{
	int i,j;
	for(i=1;i<=25;i++)
	{
		for(j=1;j<=80;j++)
		{
			gotoxy(j,i);
			textattr(color);
			cprintf(" ");
		}
	}
}
void add_shortcut(void)
{
	textattr(0x03);
	cprintf("F2");
	textattr(0x0F);
	cprintf(" Edit Contact");
	textattr(0x03);
	cprintf(" INSERT");
	textattr(0x0F);
	cprintf(" Add Contact");
	textattr(0x03);
	cprintf(" DELETE");
	textattr(0x0F);
	cprintf(" Delete Contact");
}
void add_menus(void)
{
	textattr(0x03);
	cprintf("F");
	textattr(0x0F);
	cprintf("ile   ");
	textattr(0x03);
	cprintf("V");
	textattr(0x0F);
	cprintf("iew   ");
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
			textattr(0x0F);
			//if(i==2 && j==2) printf("%c",201);
			if(i==3 && j==80) cprintf("%c",187);
			//else if(i==25 && j==2) printf("%c",200);
			else if(i==25 && j==80) cprintf("%c",188);
			else if(j==80 && i!=2) cprintf("%c",186);
			else if(i==3 || i==25) cprintf("%c",205);
		}
	}
/*
gotoxy(80,25); printf("%c",188);
*/
// gotoxy(1,1); printf("%c",201);
	textattr(0x0F);
	gotoxy(1,2); cprintf("%c",201);
	gotoxy(1,3); cprintf("%c",186);
	gotoxy(1,4); cprintf("%c",186);
	gotoxy(1,5); cprintf("%c",186);
	gotoxy(1,6); cprintf("%c",186);
	gotoxy(1,7); cprintf("%c",186);
	gotoxy(1,8); cprintf("%c",186);
	gotoxy(1,9); cprintf("%c",186);
	gotoxy(1,10); cprintf("%c",186);
	gotoxy(1,11); cprintf("%c",186);
	gotoxy(1,12); cprintf("%c",186);
	gotoxy(1,13); cprintf("%c",186);
	gotoxy(1,14); cprintf("%c",186);
	gotoxy(1,15); cprintf("%c",186);
	gotoxy(1,16); cprintf("%c",186);
	gotoxy(1,17); cprintf("%c",186);
	gotoxy(1,18); cprintf("%c",186);
	gotoxy(1,19); cprintf("%c",186);
	gotoxy(1,20); cprintf("%c",186);
	gotoxy(1,21); cprintf("%c",186);
	gotoxy(1,22); cprintf("%c",186);
	gotoxy(1,23); cprintf("%c",186);
	gotoxy(1,24); cprintf("%c",200);
	// gotoxy(1,25); printf("%c",200);
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

void print_columns(void)
{
	gotoxy(7,3);
	textattr(0x30);
	cprintf("Contact Name");

	gotoxy(33,3);
	textattr(0x30);
	cprintf("Contact Telephone");

	gotoxy(59,3);
	textattr(0x30);
	cprintf("Contact Address");
}

void draw_content(void)
{
	int i;
	for(i=3;i<=23;i++)
	{
		textattr(0x0F);
		gotoxy(27,i	);
		cprintf("%c",186);
	}
	for(i=3;i<=23;i++)
	{
		textattr(0x0F);
		gotoxy(53,i	);
		cprintf("%c",186);
	}

	for(i=2;i<=79;i++)
	{
		textattr(0x0F);
		gotoxy(i,4);
		cprintf("%c",205);
	}

	gotoxy(27,2); cprintf("%c",203);
	gotoxy(53,2); cprintf("%c",203);
	gotoxy(27,24); cprintf("%c",202);
	gotoxy(53,24); cprintf("%c",202);

	gotoxy(27,4); cprintf("%c",206);
	gotoxy(53,4); cprintf("%c",206);

	gotoxy(1,4);  cprintf("%c",204);
	gotoxy(80,4); cprintf("%c",185);

	print_columns();
}
/*
void main(void)
{
	clrscr();

	background_color(0x70);
	draw_border_shortcut(1,25);
	detectmouse ();
	showmousetext ();
	getche();
	getch();
} */