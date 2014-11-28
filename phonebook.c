#include <stdio.h>

void writefile(int phbk[][])
{
   FILE *fp;
   fp = fopen("c:\\test.txt", "w+");
   if(fp==NULL)
   {
		printf("error opening file !\n");
		exit(1);
   }
   fprintf(fp, "This is 2nd testing for fprintf...\n");
 //  fputs("This is testing for fputs...\n", fp);
   fclose(fp);
}
 void readfile()
 {
 
	FILE *fp;
   char buff[255];
   clrscr();
   fp = fopen("c:\\test.txt", "r");
   fscanf(fp, "%s", buff);
   printf("1 : %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("2: %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("3: %s\n", buff );
   fclose(fp);
   getch();
 }
 

