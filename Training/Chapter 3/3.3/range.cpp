/*
 ID: arpon.r1
 PROG: range
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXSIZE 250

int rite[MAXSIZE+1][MAXSIZE+1], down[MAXSIZE+1][MAXSIZE+1], dyn[MAXSIZE+1][MAXSIZE+1], counts[MAXSIZE-1];
char field[MAXSIZE][MAXSIZE];

int min_3(int a, int b, int c)
{
	if (a > b)
		return (b > c) ? c : b;
	return (a > c) ? c : a;
}

int main()
{
	ofstream fout("range.out");
	ifstream fin("range.in");
	int n, i, j, k;
	fin >> n;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			fin >> field[i][j];
	for (i = n - 1; i >= 0; i--)
		for (j = n - 1; j >= 0; j--)
			if (field[i][j] == '1')
			{
				rite[i][j] = rite[i][j+1] + 1;
				down[i][j] = down[i+1][j] + 1;
				dyn[i][j] = min_3(rite[i][j], down[i][j], dyn[i+1][j+1]+1);
				for (k = 2; k <= dyn[i][j]; k++)
					counts[k-2]++;
			}
	for (i = 0; i <= n - 2; i++)
		if (counts[i])
			fout << i + 2 <<  " " << counts[i] << endl;
}