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

bool edgelistcomparator(edgelist e1,edgelist e2)
{
	return (e1.weight<e2.weight);
}

int kruskalMST(vertex *network,int nodes)
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
	edgelist el[size];
	edge *e;
	cur = network;
	int i=0;
	while(cur != NULL)
	{
		e = cur->adj;
		while(e != NULL)
		{
			el[i].u = cur->vertexid;
			el[i].v = e->v->vertexid;
			el[i++].weight = e->weight;
			e=e->adj;
		}
		cur = cur->next;
	}
	sort(el,el+size,edgelistcomparator);
	i = 0;
	cout<<endl;
	while(edges != nodes - 1)
	{
		edgelist temp = el[i];
		if(!mst.isConnected(temp.u,temp.v))
		{
			cout<<"Edge Added "<<temp.u<<"-"<<temp.v<<"\nWeight = "<<temp.weight<<"\n\n";
			network_cost += temp.weight;
			edges ++;
			mst.Union(temp.u,temp.v);
		}
		i++;
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

