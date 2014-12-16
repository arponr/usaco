/*
 ID: arpon.r1
 PROB: hideseek
 LANG: C++
 */

using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define MAXN 20000

int N, M, dist[MAXN];
vector<int> adj[MAXN];
FILE *fin = fopen("hideseek.in", "r"), *fout = fopen("hideseek.out", "w");

void bfs()
{
	int que[N], read = 0, write = 1;
	memset(que, 0, sizeof(que));
	while (read < write)
	{
		int c = que[read++];
		for (int i = 0; i < adj[c].size(); i++)
		{
			int n = adj[c][i];
			if (!dist[n])
			{
				dist[n] = dist[c] + 1;
				que[write++] = n;
			}
		}
	}
}

int main()
{
	fscanf(fin, "%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int A, B;
		fscanf(fin, "%d %d", &A, &B);
		A--; B--;
		adj[A].push_back(B);
		adj[B].push_back(A);
	}
	bfs();
	int i = -1, d = 0, n = 0;
	for (int j = 1; j < N; j++)
	{
		if (dist[j] > d)
		{
			i = j;
			d = dist[j];
			n = 1;
		}
		else if (dist[j] == d)
			n++;
	}
	fprintf(fout, "%d %d %d\n", i + 1, d, n);
}
