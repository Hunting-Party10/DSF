#include<bits/stdc++.h>
#include<iostream>
#define V 5
#define infi 100000
using namespace std;
struct Graph
{
	int weight;
	int label;
	int prev;
};

int relaxation(int u,int v,Graph g[V][V])
{
	if (g[v][v].label > g[u][u].label + g[u][v].weight)
		return g[u][u].label + g[u][v].weight;
	return g[v][v].label;
}

int find_min(Graph g[V][V])
{
	int min = infi,index =-1,i;
	for( i = 1;i < V;i++)
	{
		if(g[i][i].label < min && g[i][i].prev == -1 && g[i][i].label != infi){
			min = g[i][i].label;
			index = i;
		}
	}
	cout<<"Min Lablel :"<<min<<"\n";
	return index;
}

void shortest_path(int start,Graph g[V][V])
{
	for(int i = 1;i<V;i++)
	{
		g[i][i].label = infi;
		g[i][i].prev = -1;
	}
	g[start][start].label = 0;
	int previous_vertex = start;
	for(int i = 1 ;i < V; i++)
	{
		int u = find_min(g);
		cout<<"Selected Vertex ID(Check Name Array):"<<u<<"\n\n\n";

		for(int j = 1;j<V ;j++)
		{
			if(g[u][j].weight != infi && g[j][j].prev == -1)
				g[j][j].label = relaxation(u,j,g);
		}
		g[u][u].prev = previous_vertex;
		previous_vertex = u;
	}
}


void createConnections(Graph g[V][V],char name[V][25])
{
	for(int i = 1;i<V;i++)
		for(int j = 1;j<V;j++)
			g[i][j].weight = 0;
	for(int i = 1;i < V;i++)
	{
		for(int j = 1;j < V;j++)
		{
			if(i != j){
				cout<<"Enter Weight for "<<name[i]<<" - "<<name[j]<<" (Press 0 if not edge exists): ";
				cin>>g[i][j].weight;
				if(g[i][j].weight == 0)
					g[i][j].weight = infi;
			}
			else
				g[i][j].weight = 0;
		}
	}
}


int main()
{
	cout<<"Building Network\n";
	//cout<<"Enter Number of current people on the network:";
	//cin>>V;
	cout<<"\n\n";
	Graph g[V][V];
	char name[V][25];
	for(int i=1;i<V;i++)
	{
		cout<<"Vertex Name - ";
		cin>>name[i];
	}

	createConnections(g,name);

	char query[25];
	cout<<"\n\nEnter Vertex for where you want to start :";
	cin>>query;
	int index = 0;
	for(int i=1;i<V;i++)
		if(strcmp(name[i],query)==0)
			index = i;
	if(index != 0)
		shortest_path(index,g);
		cout<<"\n\n";
		for(int i=1;i<V;i++)
			if(i != index)
				cout<<"Shortest path to Vertex - "<<name[i]<<" = "<<g[i][i].label<<"\n";
}
