/*
 ID: arpon.r1
 PROG: shuttle
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 12

int n, size, h_loc, total, dir = -1, slide = 1, mid, i;
char s[2 * MAXN + 1];
ofstream fout("shuttle.out");

void set_board()
{
	int j;
	for (j = 0; j < n; j++)
		s[j] = 'W';
	s[n] = ' ';
	for (j = n + 1; j < size; j++)
		s[j] = 'B';
}

void print(int loc)
{
	if ((i + 1) % 20 == 0 || i + 1 == total)
		fout << loc + 1 << endl;
	else
		fout << loc + 1 << ' ';
}

bool can_jump()
{
	int loc = h_loc + dir * 2;
	if (loc < 0 || loc >= size)
		return false;
	return (s[loc] != s[h_loc + dir]);
}

int main()
{
	ifstream fin("shuttle.in");
	fin >> n;
	size = 2 * n + 1;
	h_loc = n;
	total = n * n + 2 * n;
	mid = total / 2;
	set_board();
	for (i = 0; i < total; i++)
	{
		if (slide)
		{
			if (i < mid)
			{
				print(h_loc + dir);
				s[h_loc] = s[h_loc + dir];
				h_loc += dir;
				s[h_loc] = ' ';
				dir = -dir;
			}
			else
			{
				dir = -dir;
				print(h_loc + dir);
				s[h_loc] = s[h_loc + dir];
				h_loc += dir;
				s[h_loc] = ' ';
			}
			slide = 0;
		}
		else
		{
			print(h_loc + 2 * dir);
			s[h_loc] = s[h_loc + 2 * dir];
			h_loc += 2 * dir;
			s[h_loc] = ' ';
			if (!can_jump())
				slide = 1;
		}
	}
}
			