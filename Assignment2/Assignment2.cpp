#include<iostream>
#include"PriorityQueue.h"
#include<iomanip>
#define namesize 50
using namespace std;


/*
 fever-2
 cold -2
 headache -3
 drowzyness-3
 bodyache -3
 loosemotions- 4
 dizzyness -4
 loweyesight-4
 coughing  blood- 5
 inflamation-6
 chestpain -8
 total- 44
*/
typedef	struct HospitalDS
{
	int id;
	char name[namesize];
	int healthscore;
	long contact;
	int age;
}DS;


class Hospital
{
private:
	PriorityQueue<DS> pq;
	int count;
	void tabletail();
public:
	void tablehead();
	Hospital(){count = 0;}
	int	getPriority(int);
	int calculateHealthScore(int parameters[]);
	void getData();
	DS nextPatient();
	void displayPatient(DS);
	bool isEmpty();
	void getAll();
};

DS Hospital::nextPatient()
{
	count--;
	DS np=pq.dequeue();
	return np;
}
void Hospital::tabletail()
{
	for(int i=0;i<53;i++)
		cout<<"-";
	cout<<"\n";
}
void Hospital::tablehead()
{
	tabletail();
	cout<<"|Patient ID|Name        |Contact   |Age|Health Score|"<<endl;
}
void Hospital::displayPatient(DS p)
{
	tabletail();
	cout<<left<<"|"<<setw(10)<<p.id<<"|"<<setw(12)<<p.name<<"|"<<setw(10)<<p.contact<<"|"<<setw(3)<<p.age<<"|"<<setw(12)<<p.healthscore<<"|\n";
	tabletail();
}
int Hospital::getPriority(int healthscore)
{
	if(healthscore > 30)
		return 3;
	else if(healthscore<30 && healthscore>16)
		return 2;
	else
		return 1;
}

int Hospital::calculateHealthScore(int parameters[])
{
	int sum=0;
	for(int i =0 ;i<11;i++)
		sum+=parameters[i];
	return sum;
}

void Hospital::getData()
{
	count++;
	DS *obj=new DS;
	static int id=1;
	cout<<"\n\nEnter Patient Name:";
	cin.ignore();
	cin.getline(obj->name,namesize);
	cout<<"Enter Phone Number:";
	cin>>obj->contact;
	cout<<"Enter Age:";
	cin>>obj->age;
	obj->id=id;
	int choice;
	int parameters[11];
	for(int i=0;i<10;i++)
		parameters[i]=0;

	do
	{
		cout<<"\n\nEnter Symptoms\n";
		cout<<"1)Fever\n";
		cout<<"2)Cold\n";
		cout<<"3)Headache\n";
		cout<<"4)Drowzyness\n";
		cout<<"5)Bodyache\n";
		cout<<"6)Loose Motions\n";
		cout<<"7)Dizzyness\n";
		cout<<"8)Blurred Eyesight\n";
		cout<<"9)Coughing Blood\n";
		cout<<"10)Inflamation\n";
		cout<<"11)Chest Pain\n";
		cout<<"12)Exit\n";
		cout<<"Enter Choice:";
		cin>>choice;
		switch(choice)
		{
		case 1:
			parameters[choice-1]=2;
			break;
		case 2:
			parameters[choice-1]=2;
			break;
		case 3:
			parameters[choice-1]=3;
			break;
		case 4:
			parameters[choice-1]=3;
			break;
		case 5:
			parameters[choice-1]=3;
			break;
		case 6:
			parameters[choice-1]=4;
			break;
		case 7:
			parameters[choice-1]=4;
			break;
		case 8:
			parameters[choice-1]=4;
			break;
		case 9:
			parameters[choice-1]=5;
			break;
		case 10:
			parameters[choice-1]=6;
			break;
		case 11:
			parameters[choice-1]=40;
			choice=12;
			break;
		case 12:
			break;
		default:
			cout<<"Select Valid Option\n";
		}
		cout<<"Added\n";
	}
	while(choice!=12);
	obj->healthscore=0;
	for(int i=0;i<11;i++)
		obj->healthscore+=parameters[i];
	int pri=getPriority(obj->healthscore);
	cout<<pri;
	pq.enqueue(*obj,pri);
}

bool Hospital::isEmpty()
{
	if(pq.isEmpty())
		return true;
	return false;
}
void Hospital::getAll()
{
	DS *patients;
	patients=pq.sendAll(count);
	for(int i=0;i<count;i++)
		displayPatient(patients[i]);
}

int main()
{
	int choice;
	Hospital H;
	do
	{
		cout<<"\n\nPress 1 to Enter Data\n";
		cout<<"Press 2 to Get the next Patient Details\n";
		cout<<"Press 3 to display Current Patients in waiting\n";
		cout<<"Press 4 to Exit\n";
		cout<<"Enter Choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				H.getData();
				break;
			case 2:
				if(!H.isEmpty())
				{
					H.tablehead();
					H.displayPatient(H.nextPatient());
				}
				else
				{
					cout<<"Data Base is Empty\n";
				}
				break;

			case 3:
				if(!H.isEmpty())
				{
					H.tablehead();
					H.getAll();
				}
				else
				{
					cout<<"Data Base is Empty\n";
				}
				break;
			case 4:
				break;
			default:
				cout<<"Enter Valid Choice\n";
		}
	}
	while(choice !=4);
	return 0;
}
