#include<stdio.h>
#include<conio.h>
#include"LINKED.h"

void write_file(char fileName []);
void read_file(char fileName []) ;

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

void read_file(char fileName [])
{
	struct phonebook * tempstruct;
	FILE *fp;
	int i;
	int c;
	char * token;
	char tempstr [150];
	head = NULL;

	fp = fopen(fileName,"r+");
	tempstruct = head;

   while(!feof(fp))
	{
	tempstruct=create_node();
	insert_node(tempstruct);
	fscanf(fp,"%s",tempstr);
	token = strtok(tempstr,",");
	//	printf("%s \n",token);
		strcpy(tempstruct->name,token);
		token = strtok(NULL,",");
//		printf("%s \n",token);
		strcpy(tempstruct->phone,token);
		token = strtok(NULL,",");
	//	printf("%s \n",token);
		strcpy(tempstruct->address,token);


	}

	 fclose(fp);
  //	return head;
}
