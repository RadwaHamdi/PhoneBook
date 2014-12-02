#include<stdio.h>
#include<conio.h>
#include"LINKED.h"

char fileNames[6][20];
int index=0;
char currentFile[20] = NULL;

void write_file(char fileName []);
void read_file(char fileName []) ;
int delete_file(char fileName []);  //returns 0 when file is successfully deleted otherwise when error happens
FILE * open_file(char filename[]);

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
	   fprintf(fp,"%s,%s,%s",tempstruct->name,tempstruct->phone,tempstruct->address);
	   
       if(tempstruct->next !=NULL)
	  fprintf(fp,"\n");
   //   fprintf(fp, "\n  Testing...\n");
	  tempstruct = tempstruct->next;
   }
   fclose(fp);
}
//reads file in the linked list
void read_file(char fileName [])
{
	struct phonebook * tempstruct;
	FILE *fp;
	int i;
	int c;
	char * token;
	char tempstr [150];
	head = NULL;
	strcpy(currentFile,fileName);
	fp = fopen(fileName,"r+");
	tempstruct = head;

   while(!feof(fp))
	{
	tempstruct=create_node();

	fscanf(fp,"%s",tempstr);
	strcpy(token,strtok(tempstr,","));
	//	printf("%s \n",token);
		strcpy(tempstruct->name,token);
		token = strtok(NULL,",");
//		printf("%s \n",token);
		strcpy(tempstruct->phone,token);
		token = strtok(NULL,",");
	//	printf("%s \n",token);
		strcpy(tempstruct->address,token);
		insert_node(tempstruct);

	}

	 fclose(fp);
	//return head;
}
//input file name and removes it
int delete_file(char fileName [])
{
	int ret;
	ret = remove(fileName);
	index--;
	return ret;
}
//send name of file to be created

FILE * open_file(char filename[])
{
	if(index<6)
	{
		FILE * fp;
		strcat(filename,".txt");
		fp = fopen(filename,"w");
		fclose(fp);
		index++;
		return fp;
	}
	else
		return NULL;
}
//
void add_new_file(char filename[])
{
	FILE *fp;
	fp = fopen("filename.txt","ab");
	fprintf(fp,"%s ",filename);
	   //	fprintf(fp,"\n");
	fclose(fp);
}


void read_file_name(void)
{
	FILE *fp;
	char * token;
	char tempstr [150];
	fp = fopen("filename.txt","r");
	fscanf(fp,"%s",tempstr);
	(token =strtok(tempstr,",");
	while(token != NULL)
	{
		strcpy(fileNames[index],token);
		
		index++;
		token = strtok(tempstr,",");
	}
}