#include <dos.h>
//#include <graphics.h>

union REGS in, out;

void showmouse_text ()
{
	in.x.ax = 1;
	int86 (0X33,&in,&out);
}

void hide_mouse ()
{
	in.x.ax = 2;
	int86 (0X33,&in,&out);
}
void detect ()
{
	int button;

	//showmouse_text();
	while (!kbhit () )
	{
		in.x.ax = 3;
		int86 (0X33,&in,&out);
				button=out.x.bx&7;
		switch(button)
		{
			case 1:
				printf("left button pressed\n");
			break;
			case 2:
				printf("right button pressed\n");
			break;

			break;
			default:
				printf("No button pressed\n");
		   //	hide_mouse();
		}
		delay (200); // Otherwise due to quick computer response 100s of words will get print
	}
}

void detect_mouse ()
{
	in.x.ax = 0;
	int86 (0X33,&in,&out);   //invoke interrupt
	if (out.x.ax == 0)
		printf ("\nMouse Failed To Initialize");
	else
		printf ("\nMouse was Succesfully Initialized");
}


int main ()
{
	detect_mouse ();
	showmouse_text ();
		//set();
	detect ();
	hide_mouse ();
	getch ();
	return 0;
}

