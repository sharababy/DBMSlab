#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//  data structures

typedef struct Pre{
	char number[10];
} pre;


typedef struct Student
{
	char name[30];
	char rollno[30];
	char degree[30];
	char branch[30];

} student;

typedef struct Section
{
	char sid[10];
	char cnumber[10];
	int semester;
	int year;
	char faculty[30];

} section;

typedef struct Course
{
	char cname[50];
	char cnumber[10];
	int credits;
	char offeringDept[40];

} course;

typedef struct Prerequs
{
	char cnumber[10];
	pre precourse[3];


} prerequs;
typedef struct Grade
{
	char rollno[30];
	char sid[10];
	char grade[1];
	float cgpa;

} grade;


gradeToVal(char grade[])

// func signatres

int menu();
int selectRecords();
void insert(int);
void find();
void newStudent(student *s);
void newCourse(course *s);
void newSection(section *s);
void newPrerequs(prerequs *s);
void newGrade(grade *s);
int showStudentCols();
int showCourseCols();

int showSectionCols();

int showGradeCols();

int showPrerequsCols();

float findCGPA();


int main()
{
	int k,rec;

	while(1)
	{
		
		k = menu();

		if(k==1){
			rec = selectRecords();
			insert(rec);
		}
		else if(k==2){
			find();
		}
		else if(k==3){
			findCGPA();
		}
		// else if(k==4){
		// 	query();
		// }
		else{ break; }

	}
	return 0;
}



int menu(){
	int k;

	printf("\nSelect optios:\n");
	printf("\n\t1.Insert");
	printf("\n\t2.Operations");
	printf("\n\t3.Compute CG");
	//printf("\n\t4.Query");
	printf("\nYour choice: ");

	scanf("%d",&k);

	return k;

}

int selectRecords(){

	int k;

	printf("\nSelect a record:\n");
	printf("\n\t1.Student");
	printf("\n\t2.Course");
	printf("\n\t3.Section");
	printf("\n\t4.Pre Requisit");
	printf("\n\t5.Grade report");

	scanf("%d",&k);

	return k;

}


void insert(int rec){

	FILE* fp;

	if(rec ==1){

		fp = fopen("student.dat","a+");

		student new;

		newStudent(&new);

		fwrite(&new,sizeof(student),1,fp);

		//fprintf(fp,"%s %s %s %s \n",new.name,new.rollno,new.degree,new.branch);

	}
	else if(rec ==2){
		fp = fopen("course.dat","a+");

		course new;

		newCourse(&new);

		fwrite(&new,sizeof(course),1,fp);
		//fprintf(fp,"%s %s %d %s \n",new.cname,new.cnumber,new.credits,new.offeringDept);
				
	}
	else if(rec ==3){
		fp = fopen("section.dat","a+");
		
		section new;

		newSection(&new);
		fwrite(&new,sizeof(section),1,fp);
		//fprintf(fp,"%s %s %d %d %s \n",new.sid,new.cnumber,new.semester,new.year,new.faculty);
	}
	else if(rec ==4){
		fp = fopen("prerequs.dat","a+");
		
		prerequs new;

		newPrerequs(&new);

		//fprintf(fp,"%s ",new.cnumber);

		int k = 0;

				// for(k=0 ; k<10 ; k++){
				// 	fprintf(fp,"%s ",new.precourse[k].number);
				// }


		//fprintf(fp, "\n" );
		fwrite(&new,sizeof(prerequs),1,fp);

	}
	else if(rec ==5){
		fp = fopen("grade.dat","a+");

		grade new;

		newGrade(&new);

		fwrite(&new,sizeof(grade),1,fp);
		//fprintf(fp,"%s %s %s %.2f\n",new.sid,new.rollno,new.grade,new.cgpa);
		
	}

	fclose(fp);
}

void newStudent(student *s){

	printf("Enter Student details:\n");
	printf("\nName: ");
	scanf("%s",s->name);
	printf("\nRoll No.: ");
	scanf("%s",s->rollno);
	printf("\nDegree: ");
	scanf("%s",s->degree);
	printf("\nBranch: ");
	scanf("%s",s->branch);
	printf("\n");
}


void newCourse(course *s){

	printf("Enter Course details:\n");
	printf("\nName: ");
	scanf("%s",s->cname);
	printf("\nCourse No.: ");
	scanf("%s",s->cnumber);
	printf("\nCredits: ");
	scanf("%d",&s->credits);
	printf("\nOffering Dept: ");
	scanf("%s",s->offeringDept);
	printf("\n");
}


void newSection(section *s){

	printf("Enter Section details:\n");
	printf("\nSid: ");
	scanf("%s",s->sid);
	printf("\nCnumber: ");
	scanf("%s",s->cnumber);
	printf("\nSemester: ");
	scanf("%d",&s->semester);
	printf("\nYear: ");
	scanf("%d",&s->year);
	printf("\nFaculty: ");
	scanf("%s",s->faculty);
	
	printf("\n");
}


void newPrerequs(prerequs *s){

	printf("Enter Studetn details:\n");
	printf("\nCnumber: ");
	scanf("%s",s->cnumber);
	printf("\nPre Requsits: ");
	int k;

	for(k=0;k<3;k++){

		printf("\nPre Requsit %d: ",k+1);
		scanf("%s",s->precourse[k].number);
	
	}
	printf("\n");
}


void newGrade(grade *s){

	printf("Enter Grade details:\n");
	printf("\nSid: ");
	scanf("%s",s->sid);
	printf("\nRoll No.: ");
	scanf("%s",s->rollno);
	printf("\nGrade: ");
	scanf("%s",s->grade);
	s->cgpa = 0;
	printf("\n");
}



void find(){

	FILE* fp;
	int col_no;
	printf("\nOptions:");
	printf("\n1.Find all students in COE.");
	printf("\n2.Display Cname & Cnumber of courses offered in 2015");
	printf("\n3.Courses offered by a given faculty");
	printf("\n4.Find names of prerequsits of HCI");
		

	int ops;

	scanf("%d",&ops);

	int flag=0;

	if(ops==1){
		fp = fopen("student.dat","r+");
			
		student new;	

		while(1){

		size_t n = fread(&new,sizeof(student),1,fp);

		if(n < 1){
			break;
		}

			if( strcmp("COE",new.branch) == 0 ){
				printf("--> %s\n",new.name );
				flag = 1;
			}

		}

		if(flag==0){
			printf("Not Found\n");
		}
	
		
	}
	else if (ops==2)
	{		
		section new;

		fp = fopen("section.dat","r+");
		while(1){

		size_t n = fread(&new,sizeof(section),1,fp);

		if(n < 1){
			break;
		}

			if(new.year==2015 ){

				course subnew;

				FILE* fp2;

				fp2 = fopen("course.dat","r+");


				while(1){

					size_t n =  fread(&subnew,sizeof(course),1,fp2);
						if(n < 1){
							break;
						}

						if( strcmp(new.cnumber , subnew.cnumber) == 0 ){
							flag=1;
							printf("--> %s , %s\n",new.cnumber,subnew.cname );
						}

				}

				fclose(fp2);
			}


		}

		if(flag==0){
			printf("Not Found\n");
		}
	}
	else if(ops==3){
			
		section new;

		char faculty[30];

		printf("\nEnter Faculty name: ");

		scanf("%s",faculty); 

		fp = fopen("section.dat","r+"); 
		while(1){

		size_t n = fread(&new,sizeof(section),1,fp);

		if(n < 1){
			break;
		}

			if(strcmp(new.faculty , faculty) == 0 ){

				course subnew;

				FILE* fp2;

				fp2 = fopen("course.dat","r+");


				while(1){

					size_t n =  fread(&subnew,sizeof(course),1,fp2);
						if(n < 1){
							break;
						}

						if( strcmp(new.cnumber , subnew.cnumber) == 0 ){
							flag=1;
							printf("--> %s , %s\n",new.cnumber,subnew.cname );
						}

				}

				fclose(fp2);
			}


		}

		if(flag==0){
			printf("Not Found\n");
		}
	}
	else if(ops==4){
			
		prerequs new;

		char cnumber[10];

		printf("\nEnter Course Number: ");

		scanf("%s",cnumber);

		fp = fopen("prerequs.dat","r+");
		while(1){

			size_t n = fread(&new,sizeof(prerequs),1,fp);

			if(n < 1){
				break;
			}

				if(strcmp(new.cnumber , cnumber) == 0 ){

					int i;
						for(i=0;i<3;i++){
							flag=1;
							printf("--> %s\n",new.precourse[i].number );
						}
				}


		}

		if(flag==0){
			printf("Not Found\n");
		}
	}


	fclose(fp);

}


int showStudentCols(){

	int k;

	printf("\nSelect a Column:\n");
	printf("\n\t1.Name");
	printf("\n\t2.Rollno");
	printf("\n\t3.Degree");
	printf("\n\t4.Branch");

	scanf("%d",&k);

	return k;

}


int showCourseCols(){

	int k;

	printf("\nSelect a Column:\n");
	printf("\n\t1.C name");
	printf("\n\t2.C number");
	printf("\n\t3.Credits");
	printf("\n\t4.OfferingDept");

	scanf("%d",&k);

	return k;

}


int showSectionCols(){

	int k;
	
	printf("\nSelect a Column:\n");
	printf("\n\t1.Sid");
	printf("\n\t2.C number");
	printf("\n\t3.Semester");
	printf("\n\t4.Year");
	printf("\n\t5	.Faculty");
	scanf("%d",&k);

	return k;

}


int showGradeCols(){

	int k;
	
	printf("\nSelect a Column:\n");
	printf("\n\t1.Rollno");
	printf("\n\t2.Sid");
	printf("\n\t3.Grade");

	scanf("%d",&k);

	return k;

}


int showPrerequsCols(){

	int k;

	printf("\nSelect a Column:\n");
	printf("\n\t1.Cnumber");
	printf("\n\t2.Pre Requsit");
	
	scanf("%d",&k);

	return k;

}

float findCGPA(){
	
	FILE* fp;
	
	float cgpa=0;	

	float credits=0;

	printf("Enter Rollnumber: ");

	char rollno[30];

	scanf("%s",rollno)

		fp = fopen("grade.dat","r+");
			
		grade new;	

		while(1){

		size_t n = fread(&new,sizeof(grade),1,fp);

			if(n < 1){
				break;
			}

			if(strcmp(new.rollno,rollno) == 0){

					FILE* fp2;

					fp2 = fopen("section.dat","r+");
						
					section subnew;	

					while(1){

					size_t n = fread(&subnew,sizeof(section),1,fp);

						if(n < 1){
							break;
						}

						if(strcmp(subnew.sid,sid) == 0){

							fp = fopen("section.dat","r+");
						
							course subsubnew;	

								while(1){

								size_t n = fread(&subsubnew,sizeof(course),1,fp);

								if(n < 1){
								break;
									}

								if(strcmp(subnew.cnumber,subsubnew.cnumber) == 0){

									cgpa += subsubnew.credits * gradeToVal(new.grade);

									credits += subsubnew.credits;

								}

					
							}



						}

					
					}


					fclose(fp2);


			}

		
		}

		if(flag==0){
			printf("Not Found\n");
		}
	
		
	fclose(fp);

	cgpa = cgpa / credits;

	return cgpa;

}


/*

void query(){

	char colname[50],recname[50],searchcol[50],searchvalue[50];

	printf("\nQuery Syntax:\n");
	printf("\nfind <col-name> in <record-name> where <search-col> == <search-value>\n");

	printf("Record names:\n1.student\n2.course\n3.section\n4.prerequs\n5.grade\n" );

	printf("Enter your query: \n");

	scanf("find %s in %s where %s == %s",colname,recname,searchcol,searchvalue);

	FILE* fp;

	char filename[strlen(recname)+4];

	strcpy(filename,recname);

	strcat(filename,".dat");	

	fp = fopen(filename,"r+");

	student new;
	

	while(!feof(fp)){

		fread(&new,sizeof(student),1,fp);

			if( strcmp(searchvalue,   ) == 0 ){
				printf("--> %s",new.colname );
				flag = 1;
			}

		}

		if(flag==0){
			printf("Not Found\n");
		}
	
		


}

char* getString(void *str,char col[]){



	str->
}


*/
