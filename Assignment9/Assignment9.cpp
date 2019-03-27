#include<bits/stdc++.h>

using namespace std;

struct emp
{
	int id;
	char name[25];
	int phone;
	int salary;
};


class HashTable
{
	struct HT
	{
	 	emp e;
		int chain;
	};
	HT *t;
	int hash;
public:
	HashTable(int n)
	{
	 	t = new HT;
	 	hash = n;
	 	for(int i =0;i<n;i++)
	 	{
	 		t[i].e.phone = -1;
	 		t[i].chain = -1;
			strcpy(t[i].e.name,"Nothing");
			t[i].e.id = 0;
		}
	 }
	~HashTable(){delete t;}
	int insert(emp);
	void display(int);
	int search(int);
	void displayall();
};


int HashTable::insert(emp data)
{
	int i = data.phone%hash;
	if(t[i].e.phone != -1)//When there is a direct hash match
	{
		t[i].e = data;
		return i;
	}
	else
	{
		//Start Linear Probing to find the start of the chain
		int start = i;
		while(start != i-1)
		{
			if(start == hash)
				start = 0;
			if(start == t[start].e.phone % hash)
				break;
			if(t[start].e.phone == -1)
			{
				t[start].e = data;
				return start;
			}
		}
		if(start == i-1)
			return -1; //Hash Table is full

		//chain is found try finding the end of the chain
		while(t[start].chain != -1)
			start = t[start].chain;
		i = start +1;
		while(start != i-1)//next open spot after end of chain
		{
			if(i == hash)
				i = 0;
			if(t[i].e.phone == -1)
			{
				t[i].e = data;
				t[start].chain = i;
			}
			i++;
		}
	}
	return -1;
}


int HashTable::search(int query)
{
	/*
	int i = query%hash;
	if(i == t[i]->e.phone % hash)
		return i;
	else
	{
		int start = i;
		while(start != i-1)
		{
			if(start == hash)
				start = 0;
			if(start == t[start]->e.phone % hash)
				break;
			start++;
		}
		if(start == i-1)
			return -1;
		while(query != t[start]->e.phone)
	}
	return -1;
	*/
	return 0;
}

void HashTable::display(int index)
{
	cout<<index<<"\t"<<t[index].e.id<<"\t"<<t[index].e.name<<"\t"<<t[index].e.phone<<"\t"<<t[index].e.salary<<"\n";
}

void HashTable::displayall()
{
	for(int i =0 ;i<hash;i++)
		display(i);
}

int main()
{
	emp e;
	strcpy(e.name,"Hello");
	e.id = 1;
	e.phone = 400;
	e.salary = 0;
	HashTable h(10);
	h.insert(e);
	e.phone = 406;
	h.insert(e);
	e.phone = 4006;
	h.insert(e);
	e.phone = 7;
	h.insert(e);
	h.displayall();
	return 0;
}
