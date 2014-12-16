/*
 ID: arpon.r1
 PROG: concom
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;
int own[101][101], control[101][101];

void update_control(int i, int j)
{
	if (control[i][j])
		return;
	control[i][j] = 1;
	for (int x = 0; x <= 100; x++)
	{
		own[i][x] += own[j][x];
		if (own[i][x] > 50)
			update_control(i, x);
	}
	for (int y = 0; y <= 100; y++)
		if (control[y][i])
			update_control(y, j);
}

void update_own(int i, int j, int p)
{
	for (int x = 0; x <= 100; x++)
		if (control[x][i])
		{
			own[x][j] += p; 
			if (own[x][j] > 50)
				update_control(x, j);
		}
}
	
int main()
{
	ofstream fout("concom.out");
	ifstream fin("concom.in");
	for (int x = 0; x <= 100; x++)
	{
		for (int y = 0; y <= 100; y++)
		{
			if (x == y)
			{
				own[x][y] = 100;
				control[x][y] = 1;
			}
			else
			{
				own[x][y] = 0;
				control[x][y] = 0;
			}
		}
	}
	int data;
	fin >> data;
	for (int a = 0; a < data; a++)
	{
		int d, e, f;
		fin >> d >> e >> f;
		update_own(d, e, f);
	}
	for (int m = 0; m <= 100; m++)
		for (int n = 0; n <= 100; n++)
			if (control[m][n] && m != n)
				fout << m << " " << n << endl;
}