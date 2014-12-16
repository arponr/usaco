/*
ID: arpon.r1
PROG: lepr
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 200

long long matrix[MAXN][MAXN], N, best, local;

long long mod(long long in)
{
	while (in < 0) in += N;
	return (in % N);
}

int main()
{
	ofstream fout("lepr.out");
	ifstream fin("lepr.in");
	int i, j;
	fin >> N;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			fin >> matrix[i][j];
	for (i = 0; i < N; i++)
	{
		//horizontal
		local = 0;
		for (j = 0; j < N; j++)
			if (matrix[i][j] > 0) 
				local += matrix[i][j];
		if (local > best) best = local;
		
		//vertical
		local = 0;
		for (j = 0; j < N; j++)
			if (matrix[j][i] > 0)
				local += matrix[j][i];
		if (local > best) best = local;
		
		// diagonal left "/"
		local = 0;
		for (j = 0; j < N; j++)
			if (matrix[j][mod(i-j)] > 0)
				local += matrix[j][mod(i-j)];
		if (local > best) best = local;
		
		//diagonal right "\"
		local = 0;
		for (j = 0; j < N; j++)
			if (matrix[j][mod(i+j)] > 0)
				local += matrix[j][mod(i+j)];
		if (local > best) best = local;
	}
	fout << best << endl;
}