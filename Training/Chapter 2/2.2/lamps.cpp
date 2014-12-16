/*
 ID: arpon.r1
 PROG: lamps
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define INF 100000000
int n, c, states[8][102];

void make_states()
{
	//all off
	for (int i = 0; i < n; i++)
		states[0][i] = 0;
	states[0][n] = 1; states[0][n+1] = 2;
	
	//(odds || 3k+1) - (odds && 3k+1)
	for (int x = 0; x < n; x++)
		states[1][x] = 0;
	for (int y = 0; y < n; y += 2)
		states[1][y] = 1;
	for (int i = 0; i < n; i += 3)
		states[1][i] = !states[1][i];
	states[1][n] = 2; states[1][n+1] = INF;
	
	//evens on
	for (int x = 0; x < n; x++)
		states[2][x] = 0;
	for (int i = 1; i < n; i += 2)
		states[2][i] = 1;
	states[2][n] = 1; states[2][n+1] = 2;
	
	//3k+1 off
	for (int i = 1; i < n; i++)
		states[3][i] = 1;
	for (int i = 0; i < n; i += 3)
		states[3][i] = 0;
	states[3][n] = 1; states[3][n+1] = 2;
	
	//3k + 1 on
	for (int i = 1; i < n; i++)
		states[4][i] = 0;
	for (int i = 0; i < n; i += 3)
		states[4][i] = 1;
	states[4][n] = 2; states[4][n+1] = INF;
	
	//odds on
	for (int x = 0; x < n; x++)
		states[5][x] = 0;
	for (int i = 0; i < n; i += 2)
		states[5][i] = 1;
	states[5][n] = 1; states[5][n+1] = 2;
	
	//(evens || 3k+1) - (evens && 3k+1)
	for (int x = 0; x < n; x++)
		states[6][x] = 0;
	for (int y = 1; y < n; y += 2)
		states[6][y] = 1;
	for (int i = 0; i < n; i += 3)
		states[6][i] = !states[6][i];
	states[6][n] = 2; states[6][n+1] = INF;
	
	//all on
	for (int i = 0; i < n; i++)
		states[7][i] = 1;
	states[7][n] = 0; states[7][n+1] = INF;
}

int main()
{
	ofstream fout("lamps.out");
	ifstream fin("lamps.in");
	fin >> n >> c;
	int final[n];
	for (int x = 0; x < n; x++)
		final[x] = -1;
	for (int x = 2; x > 0; x--)
	{
		int temp = 1;
		while (temp != -1)
		{
			fin >> temp;
			if (temp >= 0)
				final[temp - 1] += x;
		}
	}
	make_states();
	int count = 0;
	for (int a = 0; a < 8; a++)
	{
		int b;
		if ((c >= states[a][n] && (c - states[a][n]) % 2 == 0) || (c >= states[a][n+1] && (c - states[a][n + 1]) % 2 == 0))
		{
			for (b = 0; b < n; b++)
				if (final[b] != -1 && final[b] != states[a][b])
					break;
			if (b == n)
			{
				for (b = 0; b < n; b++)
					fout << states[a][b];
				fout << endl;
				count++;
			}
		}
	}
	if (count == 0)
		fout << "IMPOSSIBLE" << endl;
	return 0;
}
	