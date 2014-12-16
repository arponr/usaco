/*
 ID: arpon.r1
 PROG: hay4sale
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	ofstream fout("hay4sale.out");
	ifstream fin("hay4sale.in");
	int C, H;
	fin >> C >> H;
	int bales[H];
	int best[C + 1];
	for (int i = 1; i <= C; i++)
		best[i] = 0;
	for (int i = 0; i < H; i++)
		fin >> bales[i];
	best[0] = 1;
	for (int a = 0; a < H; a++)
	{
		best[bales[a]] = 1;
		for (int b = 1; b + bales[a] <= C; b++)
		{
			if (best[b])
				best[b + bales[a]] = 1;
		}
	}
	int x;
	for (x = C; !best[x]; x--);
	fout << x << endl;
}
