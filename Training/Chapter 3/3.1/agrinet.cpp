/*
 ID: arpon.r1
 PROG: agrinet
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define INF 100000000
int main()
{
	ofstream fout("agrinet.out");
	ifstream fin("agrinet.in");
	int num_farms, i, j, k;
	fin >> num_farms;
	int adj[num_farms][num_farms], dist[num_farms], source[num_farms];
	bool intree[num_farms];
	for (i = 0; i < num_farms; i++)
		for (j = 0; j < num_farms; j++)
			fin >> adj[i][j];
	for (i = 0; i < num_farms; i++)
	{
		intree[i] = false;
		dist[num_farms] = INF;
		source[num_farms] = -1;
	}
	intree[0] = true;
	for (i = 0; i < num_farms; i++)
		if (adj[0][i])
		{
			dist[i] = adj[0][i];
			source[i] = 0;
		}
	int treesize = 1, cost = 0;
	while (treesize < num_farms)
	{
		int mindist = INF;
		for (j = 0; j < num_farms; j++)
			if (!intree[j] && dist[j] < mindist)
			{
				k = j;
				mindist = dist[j];
			}
		intree[k] = true;
		treesize++;
		cout << dist[k] << endl;
		cost += dist[k];
		for (j = 0; j < num_farms; j++)
			if (adj[k][j] && dist[j] > adj[k][j])
			{
				dist[j] = adj[k][j];
				source[j] = k;
			}
	}
	fout << cost << endl;
}