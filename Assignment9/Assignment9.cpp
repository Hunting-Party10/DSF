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
			t[i].e.salary = 0;
		}
	 }
	 ~HashTableReplacement(){delete[] t;}
	int insert(emp);
	void display(int);
	int search(int);
	void displayall();
};


int HashTableReplacement::insert(emp data)
{
	int i = data.phone%hash;

	if(t[i].e.phone == -1)//When there is a direct hash match and slot is empty
	{
		t[i].e = data;
		return 0;
	}
	else if(t[i].e.phone %hash == i)//When there is a direct hash match and slot is not empty
	{
		int start = i;
		//Find End of chain
		while(t[start].chain != -1)
			start = t[start].chain;
			//Linear Probe to find the next Open spot
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
		//Replace The already present data
		do
		{
			if(start == hash)
				start = 0;
			if(t[start].e.phone == -1)
				break;
			start++;
		}
		while(start != i);
		//Linear Probing finds open spot
		if(start == i)
			return -2;//table full;
		//Replace data
		t[start].e = temp;
		t[i].e = data;
		int j = t[start].e.phone % hash;
		while(t[j].chain != i)
			j = t[j].chain;
		if(t[i].chain != -1)
		{
			int chaintemp = t[i].chain;
			t[j].chain = chaintemp;
			chaintemp = t[i].chain;
			t[i].chain = -1;
			while(t[chaintemp].chain != -1)
				chaintemp = t[chaintemp].chain;
				//find end of chain and replace it with the new end chain location
			t[chaintemp].chain = start;
		}
		else
			t[j].chain = start;
		return 0;
	}
}


int HashTableReplacement::search(int query)
{

	int i = query%hash;
	if(query == t[i].e.phone)
		return i;
	else
	{
		int start = t[i].chain;
		while(start != -1)
		{
			if(t[start].e.phone == query)
				return start;
			start = t[start].chain;
		}
	}
	return -1;

}

void HashTableReplacement::display(int index)
{
	cout<<index<<"\t"<<t[index].e.id<<"\t"<<t[index].e.name<<"\t"<<t[index].e.phone<<"\t"<<t[index].e.salary<<"\t"<<t[index].chain<<"\n";
}

void HashTableReplacement::displayall()
{
	for(int i =0 ;i<hash;i++)
		display(i);
	cout<<"\n\n";
}

int main()
{
/*
	emp e;
	strcpy(e.name,"Hello");
	e.id = 1;
	e.phone = 46;
	e.salary = 0;
	HashTableReplacement h(10);
	h.insert(e);
	h.displayall();
	e.phone = 406;
	h.insert(e);
	h.displayall();
	//h.displayall();
	e.phone = 4006;
	h.insert(e);
	h.displayall();
	//h.displayall();
	//cout<<"\n\n";
	e.phone = 7;
	h.insert(e);
	h.displayall();
	e.phone = 6;
	h.insert(e);
	h.displayall();
//	e.phone = 77;
//	h.insert(e);
	e.phone  = 8;
	h.insert(e);
	h.displayall();
	cout<<h.search(406);
	return 0;
*/
}
