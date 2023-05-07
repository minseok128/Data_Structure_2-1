#include <stdio.h>
#define MAX_TERMS 101
#define MAX_COL 100
typedef struct
{
	int row;
	int col;
	int value;
} term;

void inputMatrix(term a[]);
void fastTranspose(term a[], term b[]);
void printMatrix(term a[], char);

int main()
{
	term a[MAX_COL], b[MAX_COL];

	inputMatrix(a);
	fastTranspose(a, b);
	printMatrix(a, 'A');
	printMatrix(b, 'B');
	return (0);
}

void inputMatrix(term a[])
{
	int tmp;

	printf("input size of matrix (row col) >> ");
	scanf("%d %d", &(a[0].row), &(a[0].col));
	a[0].value = 0;
	for (int i = 0; i < a[0].row; i++)
	{
		for (int j = 0; j < a[0].col; j++)
		{
			scanf("%d", &tmp);
			if (tmp != 0)
			{
				a[0].value++;
				a[a[0].value].row = i;
				a[a[0].value].col = j;
				a[a[0].value].value = tmp;
			}
		}
	}
}

void fastTranspose(term a[], term b[])
{
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;
	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++)
		{
			if (a[i].value < 0)
			{
				b[0].value--;
				for (int j = a[i].col + 1; j < numCols; j++)
					startingPos[j]--;
			}
		}
		for (i = 1; i <= numTerms; i++)
		{
			if (a[i].value < 0)
				continue;
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void printMatrix(term a[], char name)
{
	int next = 1;
	printf("\n\n\n\u25A3  %c Matrix: row=(%d), col=(%d), number of values=(%d)\n\n", name, a[0].row, a[0].col, a[0].value);
	for (int i = 0; i < a[0].row; i++)
	{
		if (i == 0)
			printf("\u250C");
		else if (i < a[0].row - 1)
			printf("\u251C");
		else
			printf("\u2514");
		for (int j = 0; j < a[0].col; j++)
		{
			if (next <= a[0].value && a[next].col == j && a[next].row == i)
				printf("%3d  ", a[next++].value);
			else
				printf("  0  ");
		}
		if (i == 0)
			printf("\u2510");
		else if (i < a[0].row - 1)
			printf("\u2524");
		else
			printf("\u2518");
		printf("\n");
	}

	printf("\n\u250C\u2500\u2500\u2500\u2500   term %c  \u2500\u2500\u2500\u2500\u2510\n", name);
	printf("\u251C%3d  \u253C%3d %3d %3d  \u2524\n", 0, a[0].row, a[0].col, a[0].value);
	printf("\u251C\u2500\u2500\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2500");
	printf("\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524\n");
	for (int i = 1; i <= a[0].value; i++)
		printf("\u251C%3d  \u253C%3d %3d %3d  \u2524\n", i, a[i].row, a[i].col, a[i].value);
	printf("\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500");
	printf("\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n");
}