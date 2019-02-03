#include<iostream>
#include"Stack.h"
#include<string.h>
#include<math.h>
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
	int	priority(char);
	char assosivity(char);
	void getExpression();
	void displayExpression();
	void displayConversion();
	double postEval();
	double preEval();
	void reverse(int);
	bool isEntered();
	double performOperation(double,double,char);
	bool validate();
};
void Assignment1::getExpression()
{
	delete exp;
	exp=new char[max];
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
			if(temp[j]== '(')
				exp[i]=')';
			else if(temp[j]==')')
				exp[i]='(';
			else
				exp[i]=temp[j];
			j--;
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
			if(temp[j]== '(')
				ans[i]=')';
			else if(temp[j]==')')
				ans[i]='(';
			else
				ans[i]=temp[j];
			j--;
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
double Assignment1::performOperation(double a,double b,char op)
{
	switch(op)
	{
	case '+':return a+b;
	case '-':return a-b;
	case '*':return a*b;
	case '/':return a/b;
	case '^':return pow(a,b);
	default:return 0.0;
	}
}
double Assignment1::postEval()
{
	postfix();
	int len=strlen(ans);
	displayConversion();
	Stack<double,max> s;
	for(int i=0;i<len;i++)
	{
		if(isalnum(ans[i]))
		{
			double x;
			cout<<"Enter Value for variable ("<<ans[i]<<"):";
			cin>>x;
			s.push(x);
		}
			else
		{
			double x=s.pop();
			double y=s.pop();
			s.push(performOperation(y,x,ans[i]));
		}
	}
	return s.pop();

}
double Assignment1::preEval()
{
	prefix();
	int len=strlen(ans);
	reverse(1);
	Stack<double,max> s;
	for(int i=0;i<len;i++)
	{
		if(isalnum(ans[i]))
		{
			double x;
			cout<<"Enter Value for variable ("<<ans[i]<<"):";
			cin>>x;
			s.push(x);
		}
		else
		{
			double x=s.pop();
			double y=s.pop();
			s.push(performOperation(x,y,ans[i]));
		}
	}
	return s.pop();
}
bool Assignment1::validate()
{
	int bracket_count=0;
	int l=strlen(exp);
	int operatorcount=0,operandcount=0;
	for(int i=0;i<l;i++)
	{
		if(bracket_count<0)
			return false;
		if(exp[i]=='(')
			bracket_count++;
		else if(exp[i]==')')
			bracket_count--;
		else if(priority(exp[i])>0)
			operatorcount++;
		else
			operandcount++;
	}
	if(operatorcount+1==operandcount && operatorcount!=0 && bracket_count==0)
		return true;
	return false;
}

int Assignment1::priority(char op)
{
	switch(op)
	{
		case '^':
			return 6;
		case '/':
			return 5;
		case '*':
			return 5;
		case '+':
			return 4;
		case '-':
			return 3;
		case '!':
			return 2;
		case '(':
			return 0;
		default:
			return -1;
	}
}
char Assignment1::assosivity(char op)
{
	switch(op)
	{
		case '^':
			return 'r';
		default:
			return 'l';
	}
}


int main()
{
	Assignment1 obj;
	int choice;
	int choice2;
	bool flag;
	do
	{
		cout<<"\n\nPress 1 to Enter Expression\n";
		cout<<"Press 2 to Convert to Prefix\n";
		cout<<"Press 3 to Convert to Postfix\n";
		cout<<"Press 4 to Evaluate\n";
		cout<<"Press 5 to exit\n";
		cout<<"Enter Choice:";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
			case 1:
				do
				{
					cout<<"\nEnter the Expression:";
					obj.getExpression();
					flag=obj.validate();
					if(!flag)
						cout<<"Please Enter a valid Expression\n";
				}
				while(!flag);
				break;
			case 2:
				cout<<"\nPretfix Form:";
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
				cout<<"\nPress 1 for Prefix Evaluation\n";
				cout<<"Press 2 for Postfix Evaluation\n";
				cout<<"Enter Choice:";
				cin>>choice2;
				switch(choice2)
				{
				case 1:
					cout<<"\nPrefix Evaluation = "<<obj.preEval();
					break;
				case 2:
					cout<<"\nPostfix Evaluation = "<<obj.postEval();
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


