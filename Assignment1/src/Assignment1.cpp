#include<iostream>
#include"stack.h"
#include"PriorityScript.h"
#include<string.h>
#define max 255
using namespace std;

void postfix(char exp[])
{
	int len=strlen(exp);
	Stack<char,max> s;
	for(int i=0;i<len;i++)
	{
		if(priority(exp[i]) == -1)
		{
			if(exp[i]==')')
			{
				do
				{
					char t=s.pop()
					if(t != '(')
						cout<<t;
				}
				while(t!='(')
			}
			else
				cout<<t;
		}
		else if(priority(exp[i]) == 0)
			s.push(exp[i]);
		else
		{
			while(priority(s.peep()) > priority(exp[i]))
				cout<<s.pop();
			if(priority(s.peep()) == priority(exp[i]) && assosivity(exp[i]) == 'l')
				cout<<s.pop();
			s.push(exp[i]);
		}
	}
}


int main()
{
	char *exp=NULL;
	int choice;
	do
	{
		cout<<"Press 1 to Enter Expression\n";
		cout<<"Press 2 to Convert to Prefix\n";
		cout<<"Press 3 to Convert to Postfix\n";
		cout<<"Press 4 to Evaluate\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
				delete exp;
				exp=new char[max];
				cin.ignore();
				cout<<"Enter the Expression";
				cin.getline(exp,max);
				break;
			case 2:
				if(exp==NULL)
					break;
				break;
			case 3:
				if(exp==NULL)
					break;
				break;
			case 4:
				if(exp==NULL)
					break;
				break;
			case 5:
				if(exp==NULL)
					break;
				break;
			default:
				cout<<"Invalid choice entered\n";
		}
	}
	while(choice!=5);
	return 0;
}

