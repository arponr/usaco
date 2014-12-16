/*
 ID: arpon.r1
 PROG: nocows
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("nocows.out");
	ifstream fin("nocows.in");
	int n, k;
	fin >> n >> k;
	int nways[k+1][n+1];
	for (int x = 0; x <= k; x++)
		nways[x][1] = 1;
	for (int a = 0; a <= n; a++)
		nways[0][a] = 0;
	for (int x = 0; x <= k; x++)
		for (int y = 2; y <= n; y++)
			nways[x][y] = 0;
	for (int i = 2; i <= k; i++)
		for (int j = 3; j <= n; j++)
			for (int p = 1; p <= j - 2; p += 2)
				nways[i][j] = (nways[i][j] + nways[i-1][p] * nways[i-1][j-p-1]) % 9901;
	fout << (nways[k][n] - nways[k-1][n] + 9901) % 9901 << endl;
}