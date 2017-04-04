#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertIntoEmployee(MYSQL *conn);

void selectFromEmployee(MYSQL *conn,int selAttr[],int num);

void updateEmployee(MYSQL *conn,int selAttr[],int num);

int main(){
	MYSQL *conn;


	char *server = "localhost";
	char *user = "root";
	char *database = "company";


	printf("\n\nWelcome to Employee Database Manager:\n");

	printf("\nEnter the password for the ROOT user: ");

	char password[] = "123";

//	scanf("%s",password);

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }


   printf("\n\nYour login was successful !\n\n");

   char menu[]="\nOptions:\n"
   				"1.Select from a given Table\n"
   				"2.Insert Into a given Table\n"
   				"3.Update Employee Table\n"
   				"4.Delete from Employee Table\n";


   printf("%s",menu);

   int selection,subSelection;

   scanf("%d",&selection);

   if (selection==1)
   {	
   		printf("\nNumber of attributes to project\n 0 for All\n");

   		int num;

   		scanf("%d",&num);

   		char attr[] = "\nAttributes in Employee Table\n"
   					  "1.Name\n"
   					  "2.Age\n"
   					  "3.SSN\n"
   					  "4.Sex\n"
   					  "5.Salary\n"
   					  "6.SuperSSN\n"
   					  "7.Dno.\n"
   					  "8.Mobile No.\n"
   					  "9.DOB\n";

   		printf("%s\n",attr);
   		int i,selAttr[9];
   		char dump;

   		for (i = 0; i < 9; ++i)
   		{
   			selAttr[i] = -1;
   		}

   		for (i = 0; i < num; ++i)
   		{
			scanf("%d",&selAttr[i]);
			scanf("%c",&dump); 			
   		}

   		selectFromEmployee(conn,selAttr,num);

   	}
   	else if (selection==2)
   	{
   		char tables[] = "\n\tWhich Table:"
   						"\n\t  1.Employee"
   						"\n\t  2.Department"
   						"\n\t  3.Project"
   						"\n\t  4.Location"
   						"\n\t  5.Works_On";
   	
   		printf("%s\n", tables);

   		int tableNo;
  		
  		scanf("%d",&tableNo);
  		if (tableNo==1)
  		{
  			insertIntoEmployee(conn);
  		}
	}

	else if (selection==3)
	{

		printf("Update Employee using:\n1.Name\n2.SSN");
   		int i,index;
   		
   		scanf("%d",&index);


   		if (index==1)
   		{
			int tmp,sal;

			char statement[1024],dump;
			unsigned long int phone;
			int sssn,dno,ssn;
			char name[20];

		scanf("%c",&dump);
		printf("\nEnter the Reference name: ");
		scanf("%[^\n]",name);
			
		printf("\nEnter the new SSN ");
		scanf("%d",&ssn);
		printf("\nEnter the salary ");
		scanf("%d",&sal);
		printf("\nEnter the super SSN ");
		scanf("%d",&sssn);
		printf("\nEnter the Department No: ");
		scanf("%d",&dno);
		printf("\nEnter the Phone No. ");
		scanf("%lu",&phone);
		snprintf(statement, 1024, "UPDATE employee SET salary=%d,ssn=%d,superssn=%d,dno=%d,mobile_no=%lu WHERE name like '%%%s%%'",sal,ssn,sssn,dno,phone,name);
		if (mysql_query(conn, statement)){
			fprintf(stderr, "%s\n", mysql_error(conn));
	      		exit(1);
		}

		printf("\nRecord successfully Updated\n");

   		}
   		else if (index==2)
   		{
			int sal;

			char statement[1024],dump;
			unsigned long int phone;
			int sssn,dno,ssn;
			char name[20];

		

		printf("\nEnter the Reference SSN ");
		scanf("%d",&ssn);
		scanf("%c",&dump);
		printf("\nEnter the new name: ");
		scanf("%[^\n]",name);
		
		printf("\nEnter the salary ");
		scanf("%d",&sal);
		printf("\nEnter the super SSN ");
		scanf("%d",&sssn);
		printf("\nEnter the Department No: ");
		scanf("%d",&dno);
		printf("\nEnter the Phone No. ");
		scanf("%lu",&phone);
		snprintf(statement, 1024, "UPDATE employee SET salary=%d,name='%s',superssn=%d,dno=%d,mobile_no=%lu WHERE ssn=%d",sal,name,sssn,dno,phone,ssn);
		
		if (mysql_query(conn, statement)) 
		{
      		fprintf(stderr, "%s\n", mysql_error(conn));
      		exit(1);
   		}
   		else{
			printf("\nRecord successfully Updated\n");   			
   		}

   		}

		
	}
	else if (selection==4)
	{
		printf("Update Employee using:\n1.Name\n2.SSN");
   		int i,index,ssn;
   		char name[20],dump;
   		scanf("%d",&index);

   		char statement[1024];

   		if (index==1)
   		{
   			scanf("%c",&dump);
   			printf("\nEnter the Reference name: ");
			scanf("%[^\n]",name);

			snprintf(statement, 1024, "Delete from employee where name = '%s'",name);
		
			if (mysql_query(conn, statement)) 
			{
	      		fprintf(stderr, "%s\n", mysql_error(conn));
	      		exit(1);
	   		}
	   		else{
				printf("\nRecord successfully deleted\n");   			
	   		}
   		}

   		else if(index==2){

   			printf("\nEnter the Reference ssn: ");
			scanf("%d",&ssn);

			snprintf(statement, 1024, "Delete from employee where ssn = %d",ssn);
		
			if (mysql_query(conn, statement)) 
			{
	      		fprintf(stderr, "%s\n", mysql_error(conn));
	      		exit(1);
	   		}
	   		else{
				printf("\nRecord successfully deleted\n");   			
	   		}

   		}
	}
   	

   	   mysql_close(conn);


	return 0;
}

void insertIntoEmployee(MYSQL *conn){

	int age,currentYear = 2017;
	unsigned long int phone;
	char sex;
	int yr,mnth,date,sal,sssn,dno,n,ssn;
	char statement[512],dump;
	printf("Enter the number of records to insert:");
	scanf("%d",&n);
	scanf("%c",&dump);
	char name[20];

	for (int i=0;i<n;i++)
	{	
		printf("\nEnter the name: ");
		scanf("%[^\n]",name);
		printf("\nEnter the SSN ");
		scanf("%d",&ssn);
		scanf("%c",&dump);
		printf("\nEnter the sex ");
		scanf("%c",&sex);
		printf("\nEnter the dob (yyyy-mm-dd)");
		scanf("%d-%d-%d",&yr,&mnth,&date);
		age = currentYear - yr;
		printf("\nEnter the salary ");
		scanf("%d",&sal);
		printf("\nEnter the super SSN ");
		scanf("%d",&sssn);
		printf("\nEnter the Department No: ");
		scanf("%d",&dno);
		printf("\nEnter the Phone No. ");
		scanf("%lu",&phone);
		snprintf(statement, 512, "INSERT INTO employee VALUES ('%s',%d,%d,'%c',%d,%d,%d,%lu,'%d-%d-%d')",name,age,ssn,sex,sal,sssn,dno,phone,yr,mnth,date);
		
		if (mysql_query(conn, statement)){
			fprintf(stderr, "%s\n", mysql_error(conn));
	      		exit(1);
		}

		printf("\nRecord successfully Inserted\n");
	}


}


void selectFromEmployee(MYSQL *conn,int selAttr[],int num){

	MYSQL_RES *res;
	MYSQL_ROW row;


	static const char *attributes[] = {
    "name",
	"age",
	"ssn",
	"sex",
	"salary",
	"superssn",
	"dno",
	"mobile_no",
	"bdate"
	};

	char query[60] = "select ";

	if (num==0){
	if (mysql_query(conn,"SELECT * from employee")) 
		{
      		fprintf(stderr, "%s\n", mysql_error(conn));
      		exit(1);
   		}
   		int i;
   		printf("\nColumns: ");
   		for (i = 0; i < 9; ++i)
   		{
			printf("%s\t",attributes[i]);

   		}
   		printf("\n");
   	}
   	else if (num>0)
   	{
   		printf("\nColumns: ");
   		int i;
   		for(i=0 ; i<num ; i++){
   			strcat(query,attributes[selAttr[i]]);
   			if (i != num-1)
   			{
	   			strcat(query,",");
   			}

   			printf("%s\t",attributes[selAttr[i]]);
   		}
   		printf("\n");

   		strcat(query," from employee");
   		if (mysql_query(conn,query)) 
		{
      		fprintf(stderr, "%s\n", mysql_error(conn));
      		exit(1);
   		}
   	}

		res = mysql_use_result(conn);

		unsigned long *lengths;
		unsigned int num_fields;

		int i;
		while ((row = mysql_fetch_row(res)) != NULL)
		{
		num_fields = mysql_num_fields(res);
		    lengths = mysql_fetch_lengths(res);
		    for(i = 0; i < num_fields; i++)
		    {
		//printf("%d",lengths[i]);
		//printf("%s\t",row[i]);
		printf("%5.*s \t", (int) lengths[i],row[i] ? row[i] : "NULL");
		         //printf("Column %u is %lu bytes in length.\n",i, lengths[i]);
		//printf("%s \n", row[i]);
		    }
		printf("\n");
		}
		      //printf("%s \n", row[0]);

		mysql_free_result(res);

}