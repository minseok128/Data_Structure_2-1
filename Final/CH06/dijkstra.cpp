#include <iostream>
#include <vector>
using namespace std;
#define INT_MAX 1'000'000'000
#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int choose(int distance[], int n, short int found[]);
void printState(int w, int n, int distance[], short int found[], int pred[]);

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[], int pred[])
{
	int i, u, w = 0;

	for (i = 0; i < n; i++)
	{
		found[i] = FALSE;
		distance[i] = cost[v][i];
		if (distance[i] != INT_MAX)
			pred[i] = v;
	}
	distance[v] = 0;
	found[v] = TRUE;
	printState(w, n, distance, found, pred);

	for (i = 0; i < n - 2; i++)
	{
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
		{
			if (!found[w])
				if (distance[u] + cost[u][w] < distance[w])
				{
					distance[w] = distance[u] + cost[u][w];
					pred[w] = u;
				}
		}
		printState(u, n, distance, found, pred);
	}
}

void printState(int u, int n, int distance[], short int found[], int pred[])
{
	cout << "\nu:" << u << '\n';
	for (int i = 0; i < n; i++)
		cout << found[i] << "  ";
	cout << " | found[]\n";
	for (int i = 0; i < n; i++)
	{
		if (distance[i] != INT_MAX)
			cout << distance[i] << "  ";
		else
			cout << "U  ";
	}
	cout << " | distance[]\n";
	for (int i = 0; i < n; i++)
		cout << pred[i] << "  ";
	cout << " | pred[]\n";
}

int choose(int distance[], int n, short int found[])
{
	int i, min, minpos;

	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
	{
		if (!found[i] && distance[i] < min)
		{
			min = distance[i];
			minpos = i;
		}
	}
	return (minpos);
}

int main()
{
	int pred[5] = {-1, -1, -1, -1, -1};
	int distance[5];
	short int found[5];
	int cost[MAX_VERTICES][MAX_VERTICES] = {
		{INT_MAX, INT_MAX, 50, 60, 3},
		{INT_MAX, INT_MAX, 10, 17, INT_MAX},
		{INT_MAX, INT_MAX, INT_MAX, INT_MAX, 30},
		{INT_MAX, INT_MAX, INT_MAX, INT_MAX, 15},
		{INT_MAX, 20, 36, INT_MAX, INT_MAX},
	};

	shortestPath(0, cost, distance, 5, found, pred);
}