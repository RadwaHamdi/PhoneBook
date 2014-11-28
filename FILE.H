#include<stdio.h>
#include<conio.h>

void write_file(char fileName []);

//write in a file function this function receives file mame as input param
//and it writes my linked list of phonebook records in it
void write_file(char fileName [])
{
  FILE *fp;
   struct phonebook node;
	struct phonebook * tempstruct = head;


	fp = fopen(fileName, "w+");

   while(tempstruct!=NULL)
   {
	 fflush(fp);
   //	fwrite(tempstruct, sizeof(struct phonebook ), 3, fp);
	   fprintf(fp,"%s,%s,%s  \n",tempstruct->name,tempstruct->phone,tempstruct->address);
   //   fprintf(fp, "\n  Testing...\n");
	  tempstruct = tempstruct->next;
   }
   fclose(fp);
}
