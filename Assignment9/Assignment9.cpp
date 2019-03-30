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
	cout<<index<<"\t"<<t[index].e.id<<"\t"<<t[index].e.name<<"\t"<<t[index].e.phone<<"\t"<<t[index].e.salary<<"\n";
}
void HashTableReplacement::displayall()
{
	for(int i =0 ;i<hash;i++)
		display(i);
	cout<<"\n\n";
}
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
	int insert(emp);
	void display(int);
	int search(int);
	void displayall();
};
int HashTable::insert(emp data)
{
	int i = data.phone%hash;

	if(t[i].e.phone == -1)//When there is a direct hash match
	{
		t[i].e = data;
		return 0;
	}
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

		if(start == i)
			return -2;//table full;
		start--;
		//cout<<"Start of chain is:"<<start<<"\n";
		while(t[start].chain != -1)
			start = t[start].chain;
		//cout<<"End of chain is:"<<start<<"\n";
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
}
int HashTable::search(int query)
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
void HashTable::display(int index)
{
	cout<<index<<"\t"<<t[index].e.id<<"\t"<<t[index].e.name<<"\t"<<t[index].e.phone<<"\t"<<t[index].e.salary<<"\n";
}
void HashTable::displayall()
{
	for(int i =0 ;i<hash;i++)
		display(i);
}
void head()
{
	cout<<"HashIndex | Employee ID| Employee Name | Phone Number | Employee Salary|\n";
}

int main()
{
	HashTable *t1 = NULL;
	HashTableReplacement *t2 = NULL;
	int choice1;
	emp e;
	do
	{
		cout<<"Press 1 for Hashing with Replacement\nPress 2 for Hasing Without Replacement\nEnter Choice:";
		cin>>choice1;
		if(choice1 == 1){
			t2 = new HashTableReplacement(20);
			break;
		}
		else if(choice1 == 2){
			t1 = new HashTable(20);
			break;
		}
		else
			cout<<"\n\nEnter Valid Choice \n";
	}
	while(choice1 != 1 || choice1 != 2);
	do {
		cout<<"\n\nPress 1 to insert Data into Table\nPress 2 to Search From the table\nPress 3 to display Complete Table\nPress 4 to Exit\nEnter Choice:";
		cin>>choice1;
		switch (choice1) {
			case 1:
				cout<<"Enter Employee ID:";
				cin>>e.id;
				cout<<"Enter Employee Name:";
				cin.getline(e.name,25);
				cout<<"Enter Phone Number:";
				cin>>e.phone;
				cout<<"Enter Salary:";
				cin>>e.salary;
				if(t1 != NULL)
				{
					if(t1->search(e.phone) == -1)
						t1->insert(e);
					else
						cout<<"Phone Number Alreay Exists\n";
				}
				else
				{
					if(t2->search(e.phone) == -1)
						t2->insert(e);
					else
						cout<<"Phone Number Alreay Exists\n";
				}
				break;
			case 2:
				cout<<"Enter Employee Phone Number:";
				cin>>e.phone;
				if(t1 != NULL)
				{
					int x = t1->search(e.phone);
					if(x == -1)
						cout<<"Record Does not Exist\n\n";
					else{
						head();
						t1->display(x);}
				}
				else
				{
					int x = t2->search(e.phone);
					if(x == -1)
						cout<<"Record Does not Exist\n\n";
					else{
						head();
						t2->display(x);}
				}
				break;
			case 3:
				if(t1 != NULL)
				{
					head();
					t1->displayall();
				}
				else
				{
					head();
					t2->displayall();
				}
				break;
			case 4:
				break;

		}
	} while(choice1 != 4);
	return 0;
}
