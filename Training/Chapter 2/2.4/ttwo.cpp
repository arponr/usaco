/*
 ID: arpon.r1
 PROG: ttwo
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

char forest[10][10];
int john[3], cows[3], moves[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void move(int* x, int* y, int* dir)
{
	int newx = *x + moves[*dir][0], newy = *y + moves[*dir][1];
	if (forest[newx][newy] != '*' && newx < 10 && newx >= 0 && newy < 10 && newy >= 0)
	{
		*x = newx; 
		*y = newy;
	}
	else
		*dir = (*dir + 1) % 4;
}

int main()
{
	ofstream fout("ttwo.out");
	ifstream fin("ttwo.in");
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			fin >> forest[x][y];
			if (forest[x][y] == 'F')
			{
				john[0] = x; 
				john[1] = y;
				john[2] = 0;
			}
			else if (forest[x][y] == 'C')
			{
				cows[0] = x; 
				cows[1] = y; 
				cows[2] = 0;
			}
		}
	}
	int minutes = 0;
	while (minutes <= 160000)
	{
		if (john[0] == cows[0] && john[1] == cows[1])
			break;
		move(&john[0], &john[1], &john[2]);
		move(&cows[0], &cows[1], &cows[2]);
		minutes++;
	}
	if (minutes <= 160000)
		fout << minutes << endl;
	else
		fout << 0 << endl;
}