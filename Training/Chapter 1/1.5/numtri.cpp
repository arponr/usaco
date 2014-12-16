/*
 ID: arpon.r1
 PROG: numtri
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("numtri.out");
	ifstream fin("numtri.in");
	int r;
	fin >> r;
	int tri[r][r];
	for (int i = 0; i < r; i++)
		for (int j = 0; j <= i; j++)
			fin >> tri[i][j];
	for (int x = r - 1; x > 0; x--)
		for (int y = 0; y < x; y++)
			tri[x - 1][y] += (tri[x][y] > tri[x][y+1]) ? (tri[x][y]) : (tri[x][y+1]);
	fout << tri[0][0] << endl;
	return 0;
}