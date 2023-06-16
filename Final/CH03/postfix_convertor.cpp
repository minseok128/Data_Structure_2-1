#include <iostream>
#include <stack>
#include <string>
using namespace std;

typedef enum {
	lparen,
	rparen,
	plus_,
	minus_,
	times,
	divide,
	mod,
	eos,
	operand
} precedence;

int isp[] = {0, 3, 1, 1, 2, 2, 2, 0};
int icp[] = {4, 3, 1, 1, 2, 2, 2, 0};

string expr;
stack<precedence> s;

precedence getToken(char *symbol, int *n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
		case '(': return (lparen);
		case ')': return (rparen);
		case '+': return (plus_);
		case '-': return (minus_);
		case '/': return (divide);
		case '*': return (times);
		case '%': return (mod);
		case '\0': return (eos);
		default: return (operand);
	}
}

void printToken(precedence t)
{
	switch (t)
	{
		case rparen : cout << ')'; break;
		case lparen : cout << '('; break;
		case plus_ :  cout << '+'; break;
		case minus_ : cout << '-'; break;
		case divide : cout << '/'; break;
		case times : cout << '*'; break;
		case mod : cout << '%'; break;
		default: break;
	}
}

void postfix(void)
{
	precedence token;
	char symbol;
	int n = 0;
	s.push(eos);

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
			cout << symbol;
		else if (token == rparen)
		{
			while (s.top() != lparen)
			{
				printToken(s.top());
				s.pop();
			}
			s.pop();
		}
		else
		{
			while (isp[s.top()] >= icp[token])
			{
				printToken(s.top());
				s.pop();
			}
			s.push(token);
		}
	}
	
	token = s.top();
	while (token != eos)
	{
		printToken(s.top());
		s.pop();
		token = s.top();
	}
}

int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	cin >> expr;
	postfix();
}