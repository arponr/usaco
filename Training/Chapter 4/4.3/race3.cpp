/*
 ID: arpon.r1
 PROG: race3
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MAXPTS 50

int npts, adjlist[MAXPTS][MAXPTS], deg[MAXPTS],
	visited[MAXPTS], visit_cmp[MAXPTS],
	unavoidable[MAXPTS], n_ua,
	splits[MAXPTS], nsplit;

void flood_fill(int cur)
{
	if (visited[cur]) return;
	visited[cur] = 1;
	for (int i = 0; i < deg[cur]; i++)
		flood_fill(adjlist[cur][i]);
}

int main()
{
	ofstream fout("race3.out");
	ifstream fin("race3.in");
	int i, j, temp;
	fin >> temp;
	while (temp != -1)
	{
		while (temp != -2)
		{
			adjlist[npts][deg[npts]++] = temp;
			fin >> temp;
		}
		npts++;
		fin >> temp;
	}
	for (i = 1; i < npts - 1; i++)
	{
		memset(visited, 0, npts * sizeof(int));
		visited[i] = 1;
		flood_fill(0);
		if (!visited[npts-1]) unavoidable[n_ua++] = i;
	}
	for (i = 1; i < npts - 1; i++)
	{
		memset(visited, 0, npts * sizeof(int));
		flood_fill(i);
		for (j = 0; j < npts; j++) visit_cmp[j] = visited[j];
		memset(visited, 0, npts * sizeof(int));
		visited[i] = 1;
		flood_fill(0);
		for (j = 0; j < npts; j++)
			if (j != i && visited[j] && visit_cmp[j])
				break;
		if (j == npts) splits[nsplit++] = i;
	}
	fout << n_ua;
	for (i = 0; i < n_ua; i++)
		fout << ' ' << unavoidable[i];
	fout << endl << nsplit;
	for (i = 0; i < nsplit; i++)
		fout << ' ' << splits[i];
	fout << endl;
}
		