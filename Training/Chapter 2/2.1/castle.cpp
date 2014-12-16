/*
 ID: arpon.r1
 PROG: castle
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;
int m, n, castle[50][50], assigned[50][50], sizes[2500], goodWall[50][50][2], room = 1;

int check_module(int x, int y, int place)
{
	if (x >= n || y >= m || x < 0 || y < 0)
		return 1;
	if (castle[x][y] & place)
		return 1;
	else 
		return 0;
}

void falsify(int x, int y, int dir, bool eq)
{
	if (!eq)
	{
		for (int a = 0; a < n; a++)
		{
			for (int b = 0; b < m; b++)
			{
				for (int c = 0; c < 2; c++)
				{
					if (a == x && b == y && c == dir)
						goodWall[a][b][c] = 1;
					else
						goodWall[a][b][c] = 0;
				}
			}
		}
	}
	else
		goodWall[x][y][dir] = 1;
}

void flood_fill(int a, int b, bool orig)
{
	if (a >= n || b >= m || a < 0 || b < 0 || assigned[a][b])
		return;
	assigned[a][b] = room;
	sizes[room - 1]++;
	bool west = castle[a][b] & 1;
	bool north = castle[a][b] & 2;
	bool east = castle[a][b] & 4;
	bool south = castle[a][b] & 8;
	if (!west && !(check_module(a, b - 1, 4)))
		flood_fill(a, b - 1, false);
	if (!north && !(check_module(a - 1, b, 8)))
		flood_fill(a - 1, b, false);
	if (!east && !(check_module(a, b + 1, 1)))
		flood_fill(a, b + 1, false);
	if (!south && !(check_module(a + 1, b, 2)))
		flood_fill(a + 1, b, false);
	if (orig)
	{
		room++;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (!assigned[i][j])
					flood_fill(i, j, true);
	}
}

int check_walls()
{
	int max = 0;
	for (int a = 0; a < n; a++)
	{
		for (int b = 1; b < m; b++)
		{
			if (assigned[a][b] != assigned[a][b - 1] && sizes[assigned[a][b] - 1] + sizes[assigned[a][b - 1] - 1] > max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a][b - 1] - 1];
				falsify(a, b - 1, 0, false);
			}
			else if (assigned[a][b] != assigned[a][b - 1] && sizes[assigned[a][b] - 1] + sizes[assigned[a][b - 1] - 1] == max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a][b - 1] - 1];
				falsify(a, b - 1, 0, true);
			}
			if (assigned[a][b] != assigned[a][b + 1] && sizes[assigned[a][b] - 1] + sizes[assigned[a][b + 1] - 1] > max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a][b + 1] - 1];
				falsify(a, b, 0, false);
			}
			else if (assigned[a][b] != assigned[a][b + 1] && sizes[assigned[a][b] - 1] + sizes[assigned[a][b + 1] - 1] == max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a][b + 1] - 1];
				falsify(a, b, 0, true);
			}
		}
	}
	for (int a = 1; a < n; a++)
	{
		for (int b = 0; b < m; b++)
		{
			if (assigned[a][b] != assigned[a - 1][b] && sizes[assigned[a][b] - 1] + sizes[assigned[a - 1][b] - 1] > max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a - 1][b] - 1];
				falsify(a, b, 1, false);
			}
			else if (assigned[a][b] != assigned[a - 1][b] && sizes[assigned[a][b] - 1] + sizes[assigned[a - 1][b] - 1] == max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a - 1][b] - 1];
				falsify(a, b, 1, true);
			}
			if (assigned[a][b] != assigned[a + 1][b] && sizes[assigned[a][b] - 1] + sizes[assigned[a + 1][b] - 1] > max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a + 1][b] - 1];
				falsify(a + 1, b, 1, false);
			}
			else if (assigned[a][b] != assigned[a + 1][b] && sizes[assigned[a][b] - 1] + sizes[assigned[a + 1][b] - 1] > max)
			{
				max = sizes[assigned[a][b] - 1] + sizes[assigned[a + 1][b] - 1];
				falsify(a + 1, b, 1, true);
			}
		}
	}
	return max;
}

int main()
{
	ofstream fout("castle.out");
	ifstream fin("castle.in");
	fin >> m >> n;
	for (int a = 0; a < n * m; a++)
		sizes[a] = 0;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			fin >> castle[x][y];
			assigned[x][y] = 0;
			for (int z = 0; z < 2; z++)
				goodWall[x][y][z] = 0;
		}
	}
	flood_fill(0, 0, true);
	fout << room - 1 << endl;
	int max = 0;
	for (int i = 0; i < room; i++)
	{
		if (sizes[i] > max)
			max = sizes[i];
	}
	fout << max << endl;
	fout << check_walls() << endl;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
			cout << assigned[x][y] << " ";
		cout << endl;
	}
	for (int x = 0; x < m; x++)
	{
		for (int y = n - 1; y >= 0; y--)
		{
			if (goodWall[y][x][1])
			{
				fout << y + 1 << " " << x + 1 << " " << "N" << endl;
				return 0;
			}
			if (goodWall[y][x][0])
			{
				fout << y + 1 << " " << x + 1 << " " << "E" << endl;
				return 0;
			}
		}
	}
	return 0;
}