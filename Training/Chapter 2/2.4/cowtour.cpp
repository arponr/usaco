/*
 ID: arpon.r1
 PROG: cowtour
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;
int n;
double dist[150][150], diams[150], fdiams[150];
int pasts[150][2], fields[150], numf = -1;

double get_dist(int a, int b, int c, int d)
{
	return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

void flood(int x)
{
	if (fields[x] != -1)
		return;
	fields[x] = numf;
	for (int y = 0; y < n; y++)
		if (dist[x][y] != 1000000)
			flood(y);
}

int main()
{
	ofstream fout("cowtour.out");
	ifstream fin("cowtour.in");
	fout.setf(ios_base::fixed, ios_base::floatfield);
	fout.precision(6);
	fin >> n;
	int adj[n][n];
	for (int a = 0; a < n; a++)
		fin >> pasts[a][0] >> pasts[a][1];
	for (int a = 0; a < n; a++)
	{
		fin.get();
		for (int b = 0; b < n; b++)
		{
			char temp;
			temp = fin.get();
			adj[a][b] = atoi(&temp);
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (adj[i][j] || i == j)
				dist[i][j] = get_dist(pasts[i][0], pasts[i][1], pasts[j][0], pasts[j][1]);
			else
				dist[i][j] = 1000000;
		}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[j][i] = dist[i][k] + dist[k][j];
	for (int x = 0; x < n; x++)
		fields[x] = -1;
	for (int x = 0; x < n; x++)
		if (fields[x] == -1)
		{
			numf++;
			flood(x);
		}
	for (int i = 0; i < n; i++)
	{
		fdiams[i] = 0;
		diams[i] = 0;
	}
	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
			if (fields[a] == fields[b] && dist[a][b] > diams[a])
				diams[a] = dist[a][b];
		if (diams[a] > fdiams[fields[a]])
			fdiams[fields[a]] = diams[a];
	}
	double min_diam = 1000000000;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fields[i] != fields[j])
			{
				double new_diam = diams[i] + diams[j] + get_dist(pasts[i][0], pasts[i][1], pasts[j][0], pasts[j][1]);
				if (new_diam < fdiams[fields[i]])
					new_diam = fdiams[fields[i]];
				if (new_diam < fdiams[fields[j]])
					new_diam = fdiams[fields[j]];
				if (new_diam < min_diam)
					min_diam = new_diam;
			}
		}
	}
	fout << min_diam << endl;
}