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

struct networkstats
{
	vertex *f;
	int fcount;
	vertex *maxcoms;
	vertex *mincoms;
	int maxcom;
	int mincom;
};

void createNetwork(struct vertex **network,char name[25],struct date dob,int comments)
{
	if(*network == NULL)
	{
		*network = new vertex;
		strcpy((*network)->name,name);
		(*network)->dob = dob;
		(*network)->adj = NULL;
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
		cur->adj = NULL;
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

networkstats netStats(vertex **v)
{
	networkstats friends;
	friends.fcount = 0;
	friends.maxcom=0;
	friends.mincom=10000;
	friends.f=NULL;
	friends.maxcoms=NULL;
	friends.mincoms=NULL;
	int fcount=0 ;
	Stack<vertex*> s;
	s.push(*v);
	//display(*v);
	while(!s.isEmpty())
	{
		vertex *temp = s.pop();
		//display(temp);
		if(temp->comments > friends.maxcom)
		{
			friends.maxcom = temp->comments;
			friends.maxcoms = temp;
		}
		if(temp->comments < friends.mincom)
		{
			friends.mincom = temp->comments;
			friends.mincoms = temp;
		}
		temp->discovered = 2; //visited
		edge *e = temp->adj;
		fcount = 0;
		while(e != NULL)
		{
			if(e->v->discovered < 1)
			{
				e->v->discovered = 1;//discovered
				s.push(e->v);
			}
			fcount ++;
			e = e->adj;
		}
		if(fcount > friends.fcount)
		{
			friends.fcount = fcount;
			friends.f = temp;
		}
	}
	return friends;
}

networkstats networkStatsBFS(vertex *network)
{
	vertex *cur = network;
	networkstats f;
	f.fcount=0;
	f.maxcom=0;
	f.mincom=10000;
	f.f=NULL;
	f.maxcoms=NULL;
	f.mincoms=NULL;
	while(cur != NULL)
	{
		networkstats temp;
		if(cur->discovered < 1)
			temp = netStats(&cur);
		else{
			cur = cur->next;
			continue;
		}
		if(temp.fcount > f.fcount)
		{
			f.fcount=temp.fcount;
			f.f = temp.f;
		}
		if(temp.maxcom > f.maxcom)
		{
			f.maxcom=temp.maxcom;
			f.maxcoms=temp.maxcoms;
		}
		if(temp.mincom < f.mincom)
		{
			f.mincom=temp.mincom;
			f.mincoms=temp.mincoms;
		}
		cur = cur->next;
	}
	return f;
}

vertex* findBday(date query,vertex **v)
{
	vertex *found= NULL;
	Stack<vertex*> s;
	s.push(*v);
	//cout<<!s.isEmpty();
	while(!s.isEmpty())
	{
		vertex *temp = s.pop();
		//display(temp);
		if(temp->dob.day == query.day && temp->dob.month == query.month && temp->dob.year == query.year)
			return temp;
		temp->discovered = 2; //visited
		edge *e = temp->adj;
		while(e != NULL )
		{
			if(e->v->discovered < 1)
				break;
			e = e->adj;
		}
		e->v->discovered = 1;//discovered
		s.push(e->v);
	}
	return NULL;
}

vertex* findBdayDFS(date query,vertex *v)
{
	vertex *cur= v,*found = NULL;
	while(cur != NULL && found == NULL)
	{
		//cout<<cur->discovered;
		if(cur->discovered < 1)
			found = findBday(query,&cur);
		cur = cur->next;
	}
	return found;
}

void reset(vertex **v)
{
	vertex *cur = *v;
	while(cur != NULL)
	{
		cur->discovered = 0;
		cur = cur->next;
	}
}

int main()
{
	char name[25];
	struct date dob;
	struct date query;
	vertex *found = NULL;
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
		cin>>name;
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
	networkstats nt = networkStatsBFS(network);
	do
	{
		cout<<"\n\n\nPress 1 to Search For person with Maximum Friends\n";
		cout<<"Press 2 to find Maximum and Minimum comments\n";
		cout<<"Press 3 to search by Birthday\n";
		cout<<"Press 4 to Exit\n";
		cout<<"Enter Choice :";
		cin>>choice;
		switch(choice)
		{
			case 1:
				display(nt.f);
				break;

			case 2:
				cout<<"\nDetails of user with Maximum Comments\n";
				display(nt.maxcoms);
				cout<<"\n\nDetails of user with Minimum Comments\n";
				display(nt.mincoms);

				break;
			case 3:
				cout<<"Enter Date of Birth to be searched\n";
				cout<<"Enter Day:";
				cin>>query.day;
				cout<<"Enter Month:";
				cin>>query.month;
				cout<<"Enter Year:";
				cin>>query.year;
				reset(&network);
				found = findBdayDFS(query,network);
				if(found == NULL)
					cout<<"\nNo Result\n";
				else{
					cout<<"\nEntry Found\n\n";
					display(found);
				}
				break;
			case 4:
				break;
			default:
				cout<<"\n Enter Valid Option\n";
		}
	}
	while(choice != 4);
}
