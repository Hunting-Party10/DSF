#include<bits/stdc++.h>

using namespace std;

struct emp
{
	int id;
	char name[25];
	int phone;
	int salary;
};


class HashTableReplacement
{
	struct HT
	{
	 	emp e;
		int chain;
	};
	HT *t;
	int hash;
public:
	HashTableReplacement(int n)
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
	int insert(emp);
	void display(int);
	int search(int);
	void displayall();
};


int HashTableReplacement::insert(emp data)
{
	int i = data.phone%hash;

	if(t[i].e.phone == -1)//When there is a direct hash match
	{
		t[i].e = data;
		return 0;
	}
	else if(t[i].phone %hash == i)
	{
		int start = i;
		while(t[start].chain != -1)
			start = t[start].chain;
		int j = start;	
		do
		{
			if(start == hash)
				start = 0;
			if(t[start].e.phone == -1)
			{
				//cout<<"Next Empty spot is:"<<start<<"\n";
				t[start].e = data;
				t[start].chain = -1;
				t[j].chain = start;
				return 0;
			}
			start++;
		}
		while(start != i);
		return -1;
	}
	else
	{	
		int start = i;
		emp temp = t[start].e;
		do
		{
			if(start == hash)
				start = 0;
			if(t[start].e.phone == -1)
				break;
			start++;
		}
		while(start != i);
		if(start == i)
			return -2;//table full;
		//cout<<"Start of chain is:"<<start<<"\n";
		t[start].e = temp;
		t[i].e = data;
		int chaintemp = t[i].chain;
		t[i].chain = -1;
		while(t[chaintemp].chain != -1)
			chaintemp = t[chaintemp].chain;
		t[chaintemp].chain = start;
	}
}


int HashTableReplacement::search(int query)
{
	
	int i = query%hash;
	if(i == t[i].e.phone % hash && query == t[i].e.phone)
		return i;
	else
	{
		int start = i;
		do
		{
			if(start == hash)
				start = 0;
			if(t[start].e.phone == -1)
				break;
			if(i == t[start].e.phone % hash)
			{
				start++;
				break;
			}
			start++;
		}
		while(start != i);
		while(start != -1 && t[start].e.phone !=query)
			start = t[start].chain;
		if(start == -1)
			return -1;
		return start;
		
	}
	return -1;
	
}

void HashTableReplacement::display(int index)
{
	cout<<index<<"\t"<<t[index].e.id<<"\t"<<t[index].e.name<<"\t"<<t[index].e.phone<<"\t"<<t[index].e.salary<<"\n";
}

void HashTableReplacement::displayall()
{
	for(int i =0 ;i<hash;i++)
		display(i);
}

int main()
{
	/*
	emp e;
	strcpy(e.name,"Hello");
	e.id = 1;
	e.phone = 400;
	e.salary = 0;
	HashTable h(10);
	h.insert(e);
	e.phone = 406;
	h.insert(e);
	//h.displayall();
	e.phone = 4006;
	h.insert(e);
	//h.displayall();
	//cout<<"\n\n";
	e.phone = 7;
	h.insert(e);
	e.phone = 6;
	h.insert(e);
	e.phone = 77;
	h.insert(e);
	//h.displayall();
	cout<<h.search(400);
	return 0;
	*/
}
