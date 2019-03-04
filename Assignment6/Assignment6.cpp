#include<iostream>
#include<string.h>
#include"Stack.h"
using namespace std;

/*
1-discovered
2-visited
*/

struct date
{
	int day;
	int month;
	int year;
};

struct vertex
{
	struct edge *adj;
	struct vertex *next;
	char name[25];
	int comments;
	struct date dob;
	int discovered;
};

struct edge
{
	struct vertex *v;
	struct edge *adj;
};

void createNetwork(struct vertex **network,char name[25],struct date dob,int comments)
{
	if(*network == NULL)
	{
		*network = new vertex;
		strcpy((*network)->name,name);
		(*network)->dob = dob;
		(*network)->comments = comments;
		(*network)->next = NULL;
		(*network)->discovered = 0;
	}
	else
	{
		vertex *cur = *network;
		while(cur->next != NULL)
			cur = cur->next;
		cur->next = new vertex;
		cur = cur->next;
		strcpy(cur->name,name);
		cur->dob = dob;
		cur->comments = comments;
		cur->next = NULL;
		cur->discovered = 0;
	}
}

bool checkfriendshipStatus(vertex *cur1,vertex *cur2)
{
	
	if(cur1->adj == NULL || cur2->adj == NULL)
	{
		//cout<<"\nList Empty";
		return false;
		
	}
	else
	{
		edge *e = cur1->adj;
		while(e != NULL)
		{
			if(e->v == cur2)
			{
				//cout<<"\nThey Are Friends";
				return true;
			}
			e = e->adj;
		}
		//cout<<"\nCould not find friend in the adj list";
		return false;
	}	
}

void createConnections(vertex **network)
{
	vertex *cur1= *network , *cur2;
	
	while(cur1 != NULL)
	{
		cout <<"\nEnter Friends for "<<cur1->name;
		int choice;	
		cur2 = *network;
		while(cur2 != NULL)
		{
			edge *temp,**t;
			if(cur2 != cur1 && !checkfriendshipStatus(cur1,cur2))
			{
				do
				{
					cout<<"\n\nIs "<<cur2->name<<" Friend of "<<cur1->name<<"?\n";
					cout<<"Press 1 to Add\nPress 2 to Skip\nEnter Choice:";
					cin>>choice;
					switch(choice)
					{
						case 1:			
							if(cur2->adj  == NULL)
							{
								cur2->adj = new edge;
								cur2->adj->v = cur1;
								cur2->adj->adj = NULL;
							}
							else
							{
								edge *cur = cur2->adj;
								while(cur->adj != NULL)
									cur= cur->adj;
								cur->adj = new edge;
								cur->adj->v = cur1;
								cur->adj->adj = NULL;
								
							}
							if(cur1->adj  == NULL)
							{
								cur1->adj = new edge;
								cur1->adj->v = cur2;
								cur1->adj->adj = NULL;
							}
							else
							{
								edge *cur = cur1->adj;
								while(cur->adj != NULL)
									cur= cur->adj;
								cur->adj = new edge;
								cur->adj->v = cur2;
								cur->adj->adj = NULL;
							}
							choice =2;
							justadded =1;
							break;
							
						case 2:
							break;
						default:
							cout<<"\nEnter Valid Choice\n";
					}
				}
				while(choice != 2);
			}
			cur2 = cur2->next;
		}
		cout<<"\nAll Possible Connections Added\n";
		cur1 = cur1->next;
	}
}

void display(vertex *v)
{
	cout<<"\nDetails of User\n";
	cout<<"Name : "<<v->name<<"\nNumber of comments:"<<v->comments<<"\nDate of Birth :"<<v->dob.day<<"-"<<v->dob.month<<"-"<<v->dob.year<<"\n"; 
} 


vertex* maxFriends(vertex **v)
{
	vertex *maxfren= *v;
	int fcount,maxcount = 0;
	Stack<vertex*> s;
	s.push(*v);
	while(!s.isEmpty())
	{
		vertex *temp = s.pop();
		temp->discovered = 2; 
		edge *e = temp->adj;
		fcount = 0;
		while(e != NULL)
		{
			if(e->v->discovered != 1)
			{
				e->v->discovered = 1;
				s.push(e->v);
			}
			fcount ++;

		}
	}
}

int main()
{
	char name[25];
	struct date dob;
	int comments;
	struct vertex *network = NULL;
	
	cout<<"Building Network\n";
	cout<<"Enter Number of current people on the network:";
	int c;
	cin>>c;
	cout<<"\nEnter Details\n";
	while(c--)
	{
		cin.ignore();
		cout<<"Name -";
		cin.getline(name,25);
		
		cout<<"Enter Date of Birth\n";
		cout<<"Enter Day:";
		cin>>dob.day;
		cout<<"Enter Month:";
		cin>>dob.month;
		cout<<"Enter Year:";
		cin>>dob.year;
		
		cout<<"Enter Number of comments:";
		cin>>comments;
		createNetwork(&network,name,dob,comments);
		cout<<"\n";
	}
	cout<<"Adding Connections\n";
	createConnections(&network);
	
	int choice;
	do
	{
		cout<<"\n\nPress 1 to Search For person with Maximum Friends\n";
		cout<<"Press 2 to find Maximum and Minimum comments\n";
		cout<<"Press 3 to search by Birthday\n";
		cout<<"Enter Choice :";
		cin>>choice;
		switch(choice)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				cout<<"\n Enter Valid Option\n";
		}
	}
	while();
}

