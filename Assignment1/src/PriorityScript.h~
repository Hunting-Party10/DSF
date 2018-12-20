//============================================================================
// Name        : Assignment1.cpp
// Author      : Atharva Joshi
// Version     :
// Copyright   : Your copyright notice
// Description : Priority Determination Script for operators
//============================================================================



int priority(char operator)
{
	switch(operator)
	{
		case '^':
			return 5;
		case '/':
			return 4;
		case '*':
			return 4;
		case '+':
			return 3;
		case '-':
			return 2;
		case '(':
			return 0;
		default:
			return -1;
	}
}
char assosivity(char operator)
{
	switch(operator)
	{
		case '^':
			return 'r';
		default:
			return 'l';
	}
}

