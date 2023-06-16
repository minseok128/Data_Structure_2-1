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

int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

string expr;
stack<char> s;

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
		else if (token == lparen)
		{
			while (s.top() != rparen)
			{
				cout << s.top();
				s.pop();
			}
			s.pop();
		}
		else
		{
			while (isp[s.top()] >= icp[token])
			{
				cout << s.top();
				s.pop();
			}
			s.push(token);
		}
	}

	while (token != eos)
	{
		cout << s.top();
		s.pop();
	}
}

int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	cin >> expr;

}