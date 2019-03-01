#include<stdio.h>
#include<string.h>
#include <stdlib.h>
void mygrep(FILE*, char*);
void myreplace(FILE *fp,char *find, char * replace);
void replacefn(char * o_string, char * s_string, char * r_string);
int  main(int argc,char *argv[])
{
	int behaviour;
	FILE *fp;
	char *filename;
	char *find;
	char * replace;

	if( argc == 4 ) {
		behaviour = 1;
		filename=argv[3];
		find=argv[2];
	}
	else if( argc == 5 ) {
		behaviour = 2;
		filename=argv[4];
		find=argv[2];
		replace = argv[3];
	}
	else if (argc < 4){
		behaviour = -1;
		printf("Too less arguments supplied.\n");
	}
	else {
		behaviour = -1;
		printf("Too many arguments supplied.\n");
	}
	if(behaviour == 1)
	{
		fp=fopen(filename,"rt");
		mygrep(fp,find);	
		fclose(fp);	
	}
	else if ( behaviour == 2 )
	{
		fp=fopen(filename,"rt");
		myreplace(fp,find,replace);	
		fclose(fp);	
	}	
	return 0;
}
void mygrep(FILE *fp,char *find)
{
	//printf("inside grep function\n");
	//printf("find: %s\n",find);
	char c[500];
	while(!feof(fp))
	{
		fgets(c,500,fp);
		if(strstr(c,find))
			printf("%s\n",c);
	}
}
void myreplace(FILE *fp,char *find, char * replace)
{
	//printf("inside replace function\n");
	//printf("find: %s\n",find);
	//printf("replace: %s\n",replace);
	
	char    *buffer;
	char    *result;
	long    numbytes;
	fseek(fp, 0L, SEEK_END);
	numbytes = ftell(fp);
	fseek(fp, 0L, SEEK_SET);	
	buffer = (char*)calloc(numbytes, sizeof(char));	
	if(buffer != NULL)
	{
		fread(buffer, sizeof(char), numbytes, fp);
		fclose(fp);
		if(strstr(buffer,find)){
			replacefn(buffer,find,replace);
		}
		printf("\n\n%s", buffer);
	}
	free(buffer);
}
void replacefn(char * o_string, char * s_string, char * r_string) {
      char buffer[strlen(o_string)];
      char * ch;
      if(!(ch = strstr(o_string, s_string)))
              return;
      strncpy(buffer, o_string, ch-o_string);
	buffer[ch-o_string] = 0;
      sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));
      o_string[0] = 0;
      strcpy(o_string, buffer);
      return replacefn(o_string, s_string, r_string);
 }

