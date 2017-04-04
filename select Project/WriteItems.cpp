#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#define File_name "Items"

using namespace std;
int serial;

//Class Items declaration
class Items
{
	private :
		//data Members
		int id;
		char name[20];
		char branch[20];
		int year;
	public :
		void Set_Details(int &serial)
		{
			cout<<++serial<<". Enter the Item details:\n";
			cout<<"Item Id: ";cin>>id;
			cout<<"Item Name: ";cin.getline(name,20);
			cout<<"Item Type: ";cin.getline(branch,20);
			cout<<"Brand: ";cin>>year;
		}

		void Get_Details(int &serial,int ifID,int ifName,int ifBranch,int ifYear)
		{
			cout<<setw(5)<<++serial;
			if(ifID!=0)
				cout<<setw(15)<<id;
			if(ifName!=0)
				cout<<setw(25)<<name;
			if(ifType!=0)
				cout<<setw(25)<<branch;
			if(ifBrand!=0)
				cout<<setw(25)<<year;
			cout<<endl;
		}
};

//write file function definition
void Write_to_File()
{
	Items item;
	char choice;
	fstream file;
	file.open(File_name,ios::app|ios::binary);
	if(!file)
		{
			cout<<"Error in creating file...\n";
			return;
		}
	do
	{
		item.Set_Item_Details(serial);
		file.write((char*)&item,sizeof(item));
		cout<<"\n\t\tPress 'y' to preceed entering more item details... ";
		cin>>choice;
		cin.get();
	}while(choice=='y');
	
	file.close();
	cout<<"Date saved into file the file.\n\n";
}

//display file function definition
void Display_File()
{
	Items item;
	fstream file;
	file.open(File_name,ios::in|ios::binary);
	if(!file)
		{
			cout<<"Error in creating file...\n";
			return;
		}
	while(file.read((char*)&item,sizeof(item)))
	{
		item.Get_Item_Details(serial,1,1,1,1);
	}
	
	file.close();
	cout<<"Date extracted file the file.\n\n";
}

//main module
int main()
{
	cout<<"\n\t\tDo you wish to enter new details? (y/N) ";
	
	//object of item class
	Items item;

	if(cin.get()=='y')
	{
		//to avoid the extra Enter accepted to interrupt the data
		cin.get();
		//writing details into file
		serial=0;
		Write_to_File();
	}

	//reading details from file
	serial=0;
	Display_File();	
	
	return 0;
}