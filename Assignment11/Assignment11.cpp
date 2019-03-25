#include<fstream>
#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;
#define NAME 25
class Fileops
{
	private:
		fstream file;
		char filename[NAME];
		class Student
		{
			private:
				int roll;
				char Name[NAME];
				int Division;
				int Marks;
				int Age;
			public:
				Student()
				{
					roll=-1;
					strcpy(Name,"NULL");
					Division=-1;
					Marks=-1;
					Age=-1;
				}
				Student(int count,char Namecpy[],int Divisioncpy,int Markscpy,int Agecpy)
				{
					roll=count;
					strcpy(Name,Namecpy);
					Division=Divisioncpy;
					Marks=Markscpy;
					Age=Agecpy;
					cout<<"Done";
				}
				void print()
				{
					Fileops temp;
					cout<<std::left<<"|"<<setw(11)<<roll<<"|"<<setw(25)<<Name<<"|"<<setw(4)<<Age<<"|"<<setw(9)<<Division<<"|"<<setw(7)<<Marks<<"|\n";
					temp.tabletail();
				}
				bool check(int cmp)
				{
					if(cmp==roll)
						return true;
					return false;
				}		
		};
	public:
		Fileops(){ }
		
		Fileops(char filenamecpy[])
		{ 
			file.open(filenamecpy,ios::ate);
			file.close();
			strcpy(filename,filenamecpy);
		}
			
		void tablehead()
		{
			tabletail();
			cout<<"|Roll Number|Student Name             |Age |Division |Marks  |\n";
			tabletail();
		}
		void tabletail()
		{
			for(int i=0;i<62;i++)
				cout<<"-";
			cout<<"\n";
		}
		void addData();
		void displayDB();
		int searchRecord(int);
		void displaysingle(int);
		void deleteRecord(int);
		void modify(int);
};


void Fileops::addData()
{
	Student S;
	char Name[NAME];
	int Age,Divison,Marks,roll;
	file.open(filename,ios::app);
	cout<<"Enter Roll Number:";
	cin>>roll;
	cout<<"Enter Student name:";
	cin.ignore();
	scanf("%[^\n]s",Name);
	cout<<"Enter Age:";
	cin>>Age;
	cout<<"Enter Marks:";
	cin>>Marks;
	cout<<"Enter Division:";
	cin>>Divison;
	S=Student(roll,Name,Divison,Marks,Age);
	file.write((char *)&S,sizeof(Student));
	file.close();
}

void Fileops::displayDB()
{

	Student S;
	file.open(filename,ios::in);
	file.read((char *)&S,sizeof(Student));
	if(!file.eof())
	{
		tablehead();
		while(!file.eof())
		{
			S.print();
			file.read((char *)&S,sizeof(Student));
		}
		
	}
	else
	{
		cout<<"Data Base Empty";
	}
	file.close();
}

void Fileops::displaysingle(int record_number)
{
	int count = 0;
	file.open(filename,ios::in);
	Student S;
	while(count != record_number)
	{
		file.read((char *)&S,sizeof(Student));
		count++;
	}
	tablehead();
	S.print();
	file.close();
}

int Fileops::searchRecord(int query)
{
	int count = 0;
	file.open(filename,ios::in);
	Student S;
	while(!S.check(query))
	{
		file.read((char *)&S,sizeof(Student));
		count++;
	}
	file.close();
	if(S.check(query))
		return count;
	return -1;
}

void Fileops::deleteRecord(int query)
{
	int count = 1;
	file.open(filename,ios::in);
	Student S;
	fstream temp;
	temp.open("temp",ios::out);
	file.read((char *)&S,sizeof(Student));
	while(!file.fail())
	{
		
		//cout<<count<<","<<query<<"\n";
		if(count != query)
		{
			cout<<"Done\n";
			temp.write((char *)&S,sizeof(Student));
		}
		file.read((char *)&S,sizeof(Student));
		count++;
	}
	file.close();
	temp.close();
	remove(filename);
	rename("temp",filename);
}

void Fileops::modify(int query)
{
	int count = 1;
	file.open(filename,ios::in);
	Student S;
	fstream temp;
	temp.open("temp",ios::out);
	file.read((char *)&S,sizeof(Student));
	while(!file.fail())
	{
		if(count != query)
		{
			temp.write((char *)&S,sizeof(Student));
		}
		else
		{
			cout<<"Enter Modified Data\n";
			char Name[NAME];
			int Age,Divison,Marks,roll;
			cout<<"Enter Roll Number:";
			cin>>roll;
			cout<<"Enter Student name:";
			cin.ignore();
			scanf("%[^\n]s",Name);
			cout<<"Enter Age:";
			cin>>Age;
			cout<<"Enter Marks:";
			cin>>Marks;
			cout<<"Enter Division:";
			cin>>Divison;
			S=Student(roll,Name,Divison,Marks,Age);
			temp.write((char *)&S,sizeof(Student));
		}	
		file.read((char *)&S,sizeof(Student));
		count++;
	}
	file.close();
	temp.close();
	remove(filename);
	rename("temp",filename);
}

int main()
{
	int choice;
	char filename[NAME];
	int query;
	int flag;
	cout<<"Enter Filename\n";
	cin.getline(filename,NAME);
	Fileops f(filename);
	int t;
	do
	{
		cout<<"\n\nStudent Data Base\n";
		cout<<"Press 1 to Add Data\n";
		cout<<"Press 2 to Display all records\n";
		cout<<"Press 3 to search for a record\n";
		cout<<"Press 4 to Modify a record\n";
		cout<<"Press 5 to delete a record\n";
		cout<<"Press 6 to Exit\n\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter number of Records you want to add:";
				cin>>t;
				while(t--)
					f.addData();
				break;
				
			case 2:
				f.displayDB();
				break;
				
			case 3:
				cout<<"Enter Roll Number you want to search:";
				cin>>query;
				flag=f.searchRecord(query);
				if(flag!=-1)
				{
					cout<<"Record Found\n";
					f.displaysingle(flag);
				}
				else
				{
					cout<<"No such Record Exists";
				}
				break;
				
			case 4:
				cout<<"Enter Roll Number you want to search:";
				cin>>query;
				flag=f.searchRecord(query);
				if(flag!=-1)
				{
					f.modify(flag);
					cout<<"Record Modified";
				}
				else
				{
					cout<<"No such Record Exists";
				}
				break;
				
			case 5:
				cout<<"Enter Roll Number you want to search:";
				cin>>query;
				flag=f.searchRecord(query);
				if(flag!=-1)
				{
					f.deleteRecord(flag);
					cout<<"Record Deleted";
				}
				else
				{
					cout<<"No such Record Exists";
				}
				break;
				
			case 6:
				break;
		}
	}
	while(choice!=6);
  		
}
