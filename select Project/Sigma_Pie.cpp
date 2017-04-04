/*
Note: give arguments wihout any special character

*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <iomanip>
#define Filename "Items"

using namespace std;
int serial;

//Class Items declaration
class Items
{
	private :
		//data Members
		char ItemId[10];
		char ItemName[20];
		char ItemType[20];
		char Brand[20];
	public :
		void SetItemDetails(int &serial)
		{
			cout<<++serial<<". Enter the Item details:\n";
			cout<<"Item Id: ";cin.getline(ItemId,10);
			cout<<"Item Name: ";cin.getline(ItemName,20);
			cout<<"Item Type: ";cin.getline(ItemType,20);
			cout<<"Brand: ";cin.getline(Brand,20);
		}

		void GetItemDetails(int &serial,int ifcounter[])
		{
			cout<<setw(5)<<++serial;
			if(ifcounter[0])
				cout<<setw(15)<<ItemId;
			if(ifcounter[1])
				cout<<setw(25)<<ItemName;
			if(ifcounter[2])
				cout<<setw(25)<<ItemType;
			if(ifcounter[3])
				cout<<setw(25)<<Brand;
			cout<<endl;
		}
		int Compare_Parameter(int i,char *a)
		{
			if(i==0)
				return(strcasecmp(ItemId,a));
			if(i==1)
				return(strcasecmp(ItemName,a));
			if(i==2)
				return(strcasecmp(ItemType,a));
			if(i==3)
				return(strcasecmp(Brand,a));
		}
};

//find in query statement function definition
int find_in_query_statement(char *argv[],const char *a,int argc)
{
	for(int k=1;k<argc;k++)
		if(strcasecmp(argv[k],a)==0)
			return k;
	return 0;
}

//print table headings
void Print_Table_Headings(int a[])
{
	cout<<setw(5)<<"S.No.";
	if(a[0])
		cout<<setw(15)<<"ItemId";
	if(a[1])
		cout<<setw(25)<<"ItemName";
	if(a[2])
		cout<<setw(25)<<"ItemType";
	if(a[3])
		cout<<setw(25)<<"Brand";
	cout<<endl<<endl;
}

//main module
int main(int argc,char *argv[])
{
	int ifcounter[4]={0};

	const char *field[4]={"ItemId","ItemName","ItemType","Brand"};
	int i=1;

	//finding position of where and from so as to use in the query
	int where_index=find_in_query_statement(argv,"where",argc);
	int from_index=find_in_query_statement(argv,"from",argc);

	if(from_index)
		if(strcasecmp(argv[from_index+1],Filename))
			{
				cout<<"\n\t\tFrom Table doesn't exist\n";
				return -1;
			}
		else
			cout<<"\n\t\tFrom Table exists\n";
	else
		{
			cout<<"\n\t\tFrom Keyword missing, can't fetch table\n";
			return -1;
		}
	//printing the query heading
	cout<<endl;
	for(int j=1;j<argc;j++)
		cout<<argv[j]<<"  ";
	cout<<";"<<endl;

	//project module
	if(strcasecmp(argv[i],"project")==0)
	{
		i++;
		if(strcasecmp(argv[i],"all")==0)
			for(int j=0;j<4;j++)
				ifcounter[j]++;
		else
			{
				int sum=0;
				while(i<from_index)
				{
					for(int j=0;j<4;j++)
						if(strcasecmp(argv[i],field[j])==0)
							{
								ifcounter[j]++;
								sum+=ifcounter[j];
							}
					i++;
				}
				if(!sum)
				{
					cout<<"\n\t\tNo fields selected\n";
					return -1;
				}
			}
		Items item;
		fstream file;
		file.open(Filename,ios::in|ios::binary);
		if(!file)
		{
			cout<<"\n\t\tError in fetching table...\n";
			return -1;
		}
		Print_Table_Headings(ifcounter);
		serial=0;
		while(file.read((char*)&item,sizeof(item)))
		{
			item.GetItemDetails(serial,ifcounter);
		}
		cout<<"\n\n\t"<<serial<<" tuples found for the Query\n\n";
		file.close();
		return 0;
	}
	else
		//Select module
		if(strcasecmp(argv[i],"select")==0)
		{
			i++;int success;
			if(strcasecmp(argv[i],"all")==0)
				for(int j=0;j<4;j++)
					ifcounter[j]++;
			else
				{
					int sum=0;
					while(i<from_index)
					{
						for(int j=0;j<4;j++)
							if(strcasecmp(argv[i],field[j])==0)
								{
									ifcounter[j]++;
									sum+=ifcounter[j];
								}
						i++;
					}
					if(!sum)
					{
						cout<<"\n\t\tNo fields selected\n";
						return -1;
					}
				}

			Items item;
			fstream file;
			file.open(Filename,ios::in|ios::binary);
			if(!file)
			{
				cout<<"\n\t\tError in fetching table...\n";
				return -1;
			}
			Print_Table_Headings(ifcounter);
			serial=0;
			while(file.read((char*)&item,sizeof(item)))
			{
				if(where_index)
					{
						if(strcasecmp(argv[where_index+2],"=")==0)
						{
							if(strcasecmp(argv[where_index+1],field[0])==0)
								(item.Compare_Parameter(0,argv[where_index+3]))?success=0:success=1;
							else
								if(strcasecmp(argv[where_index+1],field[1])==0)
									(item.Compare_Parameter(1,argv[where_index+3]))?success=0:success=1;
								else
									if(strcasecmp(argv[where_index+1],field[2])==0)
										(item.Compare_Parameter(2,argv[where_index+3]))?success=0:success=1;
									else
										if(strcasecmp(argv[where_index+1],field[3])==0)
											(item.Compare_Parameter(3,argv[where_index+3]))?success=0:success=1;
										else cout<<"\t\t\nInvalid Column name in Where clause\n";
						}
						else
						{
							cout<<"\n\t\tWhere Clause missing an \"Equal to operator\" ...\n";
							return -1;
						}
					}
				else
					success++;
				if(success)
					item.GetItemDetails(serial,ifcounter);
			}
			cout<<"\n\n\t"<<serial<<" tuples found for the Query\n\n";
			file.close();
			return 0;
		}
	return 0;
}