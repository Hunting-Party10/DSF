#include<iostream>
#include"UF.h"
#include<string.h>
using namespace std;


struct vertex
{
	struct edge *adj;
	struct vertex *next;
	char name[25];
	int vertexid;
};

struct edge
{
	struct vertex *v;
	struct edge *adj;
	int weight;
};

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

void createNetwork(struct vertex **network,char name[25],int id)
{
	if(*network == NULL)
	{
		*network = new vertex;
		strcpy((*network)->name,name);
		(*network)->adj = NULL;
		(*network)->next = NULL;
		(*network)->vertexid = id;
	}
	else
	{
		vertex *cur = *network;
		while(cur->next != NULL)
			cur = cur->next;
		cur->next = new vertex;
		cur = cur->next;
		strcpy(cur->name,name);
		cur->next = NULL;
		cur->adj = NULL;
		cur->vertexid = id;
	}
}

void createConnections(vertex **network)
{
	vertex *cur1= *network , *cur2;
	int weight;
	
	while(cur1 != NULL)
	{
		cout <<"\nEnter Adjecent Edges for "<<cur1->name;
		int choice;	
		cur2 = *network;
		while(cur2 != NULL)
		{
			
			if(cur2 != cur1 && !checkfriendshipStatus(cur1,cur2))
			{
				do
				{
					cout<<"\n\nIs "<<cur2->name<<" connected to "<<cur1->name<<"?\n";
					cout<<"Press 1 to Yes\nPress 2 to No\nEnter Choice:";
					cin>>choice;
					switch(choice)
					{
						case 1:	
							cout<<"Enter Weight of the Edge:";
							cin>>weight;
							cout<<"\n\n";
							if(cur2->adj  == NULL)
							{
								cur2->adj = new edge;
								cur2->adj->v = cur1;
								cur2->adj->adj = NULL;
								cur2->adj->weight = weight;
								
							}
							else
							{
								edge *cur = cur2->adj;
								while(cur->adj != NULL)
									cur= cur->adj;
								cur->adj = new edge;
								cur->adj->v = cur1;
								cur->adj->adj = NULL;
								cur2->adj->weight = weight;
								
							}
							if(cur1->adj  == NULL)
							{
								cur1->adj = new edge;
								cur1->adj->v = cur2;
								cur1->adj->adj = NULL;
								cur1->adj->weight = weight;
							}
							else
							{
								edge *cur = cur1->adj;
								while(cur->adj != NULL)
									cur= cur->adj;
								cur->adj = new edge;
								cur->adj->v = cur2;
								cur->adj->adj = NULL;
								cur->adj->weight =weight;
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

int kruskalMST(vertex *network,int size)
{
	UF mst(size);
	int edges = 0;
	int min_weight = 1000000;
	int network_cost =0;
	vertex *cur;
	edge *e,*minedge;
	while(edges != size-1)
	{
		cur = network;
		min_weight = 1000000;
		while(cur != NULL)
		{
			e = cur->adj;
			while(e != NULL)
			{
				if(!mst.isConnected(cur->vertexid,e->v->vertexid) && e->weight < min_weight){
					min_weight = e->weight;	
					minedge = e;		
				}
				e = e->adj;
			}
			mst.Union(cur->vertexid,minedge->v->vertexid);
			mst.Union(0,cur->vertexid);
			network_cost += min_weight;
			cur = cur->next;
		}
	}
	return network_cost;
}

int main()
{
	char name[25];
	vertex *network = NULL;
	cout<<"Building Network\n";
	cout<<"Enter Number of current people on the network:";
	int c,id =1;
	cin>>c;
	int size = c;
	while(c--)
	{
		cin.ignore();
		cout<<"Vertex Name -";
		cin>>name;
		createNetwork(&network,name,id);
		id++;
	}
	cout<<"Adding Connections\n";
	createConnections(&network);
	
	cout<<"Finding MST";
	cout<<"Cost of MST is :"<<kruskalMST(network,size);
	
}

