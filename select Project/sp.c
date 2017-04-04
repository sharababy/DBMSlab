#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee
{	
	char name[20];
	int ssn;
	int day;
	int month;
	int year;
	int superssn;
	int dno;

} employee;


int main(int argc, char const *argv[])
{
	int i=0;

	FILE* docs;

	char *tables[] = {"employee","departments"};

	int tableCount = 2;

	char inital[] ="Query: ";

	printf("\n\t%s", inital);

	for (i = 1; i < argc; ++i)
	{
		printf("%s\n ",argv[i] );
	}
	printf("\n");


	employee e;

	strcpy(e.name,"Bano Billa");
	e.dno = 105;
	e.ssn = 29193;
	e.day = 20;
	e.month = 10;
	e.year = 1997;
	e.superssn = 1001;

	FILE* fill  = fopen("employee" , "w+");

	for ( i = 0; i < 10; ++i)
	{
		/*fprintf(fill, "%s\n", e.name);
		fprintf(fill, "%d\n", e.dno );
		fprintf(fill, "%d\n", e.ssn );
		fprintf(fill, "%d\n", e.superssn);
		fprintf(fill, "%d\n", e.day );
		fprintf(fill, "%d\n", e.month);
		fprintf(fill, "%d\n", e.year);*/

		fprintf(fill, "%s\n",&e);
	}


	int qcount=0;
	if(++qcount<=argc)
	if (strcmp(argv[qcount],"select")==0)
	{

		if(++qcount<=argc){
		if(strcmp(argv[qcount],"all")==0){

			if(++qcount<=argc)
			if (strcmp(argv[qcount],"from") == 0)
			{	
				if(++qcount<=argc)
				for ( i = 0; i < tableCount; ++i)
				{	


					if (strcmp(argv[qcount],tables[i])==0)
					{	

						employee temp;

						docs = fopen(tables[i],"r+");

						char check;
						char dump;
							
						fseek(docs,0,SEEK_SET);

						int count = 0;

						while(count < 10){

						 	/*fscanf(docs,"%s\n",temp.name );
							fscanf(docs,"%d\n",&temp.dno );
							fscanf(docs,"%d\n",&temp.ssn );
							fscanf(docs,"%d\n",&temp.superssn );
							fscanf(docs,"%d\n",&temp.day );
							fscanf(docs,"%d\n",&temp.month );
							fscanf(docs,"%d\n",&temp.year );*/

							fread(&temp,sizeof(employee),1,docs);
						
						 	printf("name=%s ssn=%d dno=%d super=%d %d/%d/%d \n",temp.name,temp.ssn,temp.dno,temp.superssn,temp.day,temp.month,temp.year );

						 	count++;
						}
					}

				}
				

			}

		}
		else{

		}
		}	
	}


	fclose(fill);
	fclose(docs);
	return 0;
}