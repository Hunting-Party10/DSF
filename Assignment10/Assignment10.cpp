
#include<bits/stdc++.h>
#include"UF.h"
using namespace std;
struct vertex
{
	struct edge *adj;
	struct vertex *next;
	char name[25];
	int vertexid;
	int edgecount;
};

struct edge
{
	struct vertex *v;
	struct edge *adj;
	int weight;
};

struct edgelist
{
	int u;
	int v;
	int weight;
};

bool checkfriendshipStatus(vertex *cur1,vertex *cur2)
{

	if(cur1->adj == NULL || cur2->adj == NULL)
		return false;
	else
	{
		edge *e = cur1->adj;
		while(e != NULL)
		{
			if(e->v == cur2)
				return true;
			e = e->adj;
		}
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
		(*network)->edgecount = 0;
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
		cur->edgecount=0;
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
								cur->adj->weight = weight;

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
							cur1->edgecount++;
							cur2->edgecount++;
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
int prim(vertex *network,vertex *start,int nodes)
{
	if(network == NULL)
		return  0;
	int size = 0;
	int edges = 0;
	int network_cost = 0;
	vertex *cur = network;
	while(cur != NULL)
	{
		size += cur->edgecount;
		cur = cur->next;
	}
	UF mst(size);

	mst.Union(0,start->vertexid);
	while(edges != nodes-1)
	{
		vertex *minimum = NULL;
		int mincost = 10000000;
		vertex *temp = network;
		edgelist el;
		while(temp != NULL)
		{
			if(mst.isConnected(temp->vertexid,0))
			{
				edge *temp2 = temp->adj;
				while(temp2 != NULL)
				{
					if(temp2->weight < mincost && !mst.isConnected(0,temp2->v->vertexid))
					{
						minimum = temp2->v;
						mincost = temp2->weight;
						el.u = temp->vertexid;
						el.v= temp2->v->vertexid;
					}
					temp2=temp2->adj;
				}
			}
			temp = temp->next;
		}
		mst.Union(0,minimum->vertexid);
		cout<<"Edge Added "<<el.u<<"-"<<el.v<<"\nWeight = "<<mincost<<"\n\n";
		network_cost +=mincost;
		edges++;
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
	cout<<"\n\n";
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

	cout<<"Enter Start Vertex";
	char start[25];
	cin>>start;
	vertex *cur = network;
	while(cur != NULL)
	{
		if(strcmp(cur->name,start) == 0)
			break;
		cur = cur->next;
	}
	int networkcost;
	if(cur != NULL)
		networkcost = prim(network,cur,size);
	else
		networkcost = 0;
	cout<<"\n\n";
	cout<<"Telephone line Cost = "<<networkcost;
	return 0;
}
