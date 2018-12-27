#include<iostream>
#include"Stack.h"
#include"PriorityScript.h"
#include<string.h>
#define max 255
using namespace std;

class Assignment1
{
private:
	char *exp;
	char *ans;
public:
	Assignment1()
{
		exp=NULL;
		ans=NULL;
}
	~Assignment1()
	{
		delete exp;
		delete ans;
	}
	void postfix();
	void prefix();
	void getExpression();
	void displayExpression();
	void displayConversion();
	float postEval();
	float preEval();
	void reverse(int);
	bool isEntered();
};

void Assignment1::getExpression()
{
	delete exp;
	exp=new char[max];
	cin.ignore();
	cin.getline(exp,max);
}
void Assignment1::displayExpression()
{
	cout<<exp<<"\n";
}
void Assignment1::postfix()
{
	delete ans;
	int len=strlen(exp);
	ans=new char(len);
	int k=0;
	Stack<char,max> s;
	for(int i=0;i<len;i++)
	{
		if(priority(exp[i]) == -1)
		{
			if(exp[i]==')')
			{
				char t;
				do
				{
					t=s.pop();
					if(t != '(')
						ans[k++]=t;
				}
				while(t!='(');
			}
			else
				ans[k++]=exp[i];
		}
		else if(priority(exp[i]) == 0)
			s.push(exp[i]);
		else
		{
			while(priority(s.peep()) > priority(exp[i]))
				ans[k++]=s.pop();
			if(priority(s.peep()) == priority(exp[i]) && assosivity(exp[i]) == 'l')
				ans[k++]=s.pop();
			s.push(exp[i]);
		}
	}
	while(!s.isEmpty())
		ans[k++]=s.pop();
}
void Assignment1::displayConversion()
{
	cout<<ans;
}
void Assignment1::reverse(int k)
{
	if(k == 0)
	{
		char temp[max];
		strcpy(temp,exp);
		int len=strlen(exp);
		int j=len-1;
		for(int i=0;i<len;i++)
		{
			exp[i]=temp[j--];
		}
	}
	else if(k == 1)
	{
		char temp[max];
		strcpy(temp,ans);
		int len=strlen(ans);
		int j=len-1;
		for(int i=0;i<len;i++)
		{
			ans[i]=temp[j--];
		}
	}
}
void Assignment1::prefix()
{
	delete ans;
	reverse(0);
	int len=strlen(exp);
	ans=new char(len);
	int k=0;
	Stack<char,max> s;
	for(int i=0;i<len;i++)
	{
		if(priority(exp[i]) == -1)
		{
			if(exp[i]==')')
			{
				char t;
				do
				{
					t=s.pop();
					if(t != '(')
						ans[k++]=t;
				}
				while(t!='(');
			}
			else
				ans[k++]=exp[i];
		}
		else if(priority(exp[i]) == 0)
			s.push(exp[i]);
		else
		{
			while(priority(s.peep()) > priority(exp[i]))
				ans[k++]=s.pop();
			if(priority(s.peep()) == priority(exp[i]) && assosivity(exp[i]) == 'r')
				ans[k++]=s.pop();
			s.push(exp[i]);
		}
	}
	while(!s.isEmpty())
	ans[k++]=s.pop();
	reverse(0);
	reverse(1);
}
bool Assignment1::isEntered()
{
	if(exp == NULL)
		return false;
	return true;
}
float Assignment1::postEval()
{
	postfix();
	return 0;
}

float Assignment1::preEval()
{
	prefix();
	return 0;
}


int main()
{
	Assignment1 obj;
	int choice;
	int choice2;
	do
	{
		cout<<"\n\nPress 1 to Enter Expression\n";
		cout<<"Press 2 to Convert to Prefix\n";
		cout<<"Press 3 to Convert to Postfix\n";
		cout<<"Press 4 to Evaluate\n";
		cout<<"Press 5 to exit\n";
		cout<<"Enter Choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\nEnter the Expression:";
				obj.getExpression();
				break;
			case 2:
				cout<<"\nPostfix Form:";
				obj.prefix();
				obj.displayConversion();
				break;
			case 3:
				cout<<"\nPostfix Form:";
				obj.postfix();
				obj.displayConversion();
				break;
			case 4:
				if(!obj.isEntered())
					break;
				cout<<"Press 1 for Prefix Evaluation\n";
				cout<<"Press 2 for Postfix Evaluation\n";
				cout<<"Enter Choice:";
				cin>>choice2;
				switch(choice2)
				{
				case 1:
					cout<<"Evaluation = "<<obj.preEval();
					break;
				case 2:
					cout<<"Evaluation = "<<obj.postEval();
					break;
				case 3:
					break;
				default:
					cout<<"Enter Valid Option";
				}
				break;
			case 5:
				break;
			default:
				cout<<"Invalid choice entered\n";
		}
	}
	while(choice!=5);
	return 0;
}
