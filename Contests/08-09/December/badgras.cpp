/*
ID: arpon.r1
PROG: badgras
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
int field[1000][1000], assigned[1000][1000], island = 0, r, c;

void search(int x, int y)
{
	if (x >= r || y >= c || x < 0 || y < 0 || assigned[x][y])
		return;
	assigned[x][y] = 1;
	if (field[x+1][y] && !assigned[x+1][y])
		search(x + 1, y);
	if (field[x-1][y] && !assigned[x-1][y])
		search(x - 1, y);
	if (field[x][y + 1] && !assigned[x][y + 1])
		search(x, y + 1);
	if (field[x][y - 1] && !assigned[x][y - 1])
		search(x, y - 1);
	if (field[x+1][y + 1] && !assigned[x+1][y + 1])
		search(x + 1, y + 1);
	if (field[x+1][y-1] && !assigned[x+1][y-1])
		search(x + 1, y - 1);
	if (field[x-1][y+ 1] && !assigned[x-1][y+1])
		search(x + 1, y);
	if (field[x-1][y-1] && !assigned[x-1][y-1])
		search(x - 1, y - 1);
}

int main()
{
	ofstream fout("badgras.out");
	ifstream fin("badgras.in");
	fin >> r >> c;
	for (int x = 0; x < r; x++)
	{
		for (int y = 0; y < c; y++)
		{
			fin >> field[x][y];
			assigned[x][y] = 0;
		}
	}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			if (!assigned[i][j])
			{
				search(i, j);
				island++;
			}
		}
	fout << island << endl;
}

