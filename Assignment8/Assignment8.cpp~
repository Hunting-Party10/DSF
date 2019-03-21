#include<bits/stdc++.h>
#define inf 999999
struct Graph
{
	int weight;
	int label;
};

void shortestpath(Graph **g,int start,int size)
{
	for(int i = 1;i<=size;i++)
		g[i][i].label = inf;
	
	g[start][start].label = 0;
	int current = start;
	
	int temp;
	for(int i = current + 1; i<=size; i++)
	{
	 	if(g[current] != 0)
	 	{
		}
	}
	
}

void createConnections()
{
	for(int i = 1;i<=size;i++)
		for(int j = 1;j<=size;j++)
			g[i][j].weight = 0;
	for(int i = 1;i <= size;i++)
	{
		for(int j = i;j <= size;j++)
		{
			cout<<"Enter Weight for "<<name[i-1]<<" - "<<name[j-1]<<" : ";
			cin>>g[i][j];
			g[j][i] = g[i][j];
`		}
			
	}
}


int main()
{
	cout<<"Building Network\n";
	cout<<"Enter Number of current people on the network:";
	int size;
	cin>>size;
	cout<<"\n\n";
	Graph g[size + 1][size + 1];
	char name[size][25];
	for(int i=0;i<size;i++)
	{
		cout<<"Vertex Name - ";
		cin>>name[i];
	}
	
	createConnections(g,size);
	
	char query[25];
	cout<<"\n\nEnter Vertex for where you want to start :";
	cin>>query;
	int index = 0;
	for(int i=0;i<size;i++)
		if(strcmp(name[i],query)==0)
			index = i;
			
	if(index != 0)
		shortestpath(g,index,size);
	
}
