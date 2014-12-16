/*
 ID: arpon.r1
 PROG: sandcas
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 25000

int n, x, y, cur[MAXN], want[MAXN], used[MAXN];

int main()
{
	FILE *fin = fopen("sandcas.in", "r"), *fout = fopen("sandcas.out", "w");
	int i, j, cur_cost, min_cost, min_index, output = 0;
	fscanf(fin, "%d %d %d", &n, &x, &y);
	for (i = 0; i < n; i++)
		fscanf(fin, "%d %d", &cur[i], &want[i]);
	for (i = 0; i < n; i++)
	{
		min_cost = 100000000;
		for (j = 0; j < n; j++)
			if (!used[j])
			{
				if (cur[j] < want[i])
					cur_cost = x * (want[i] - cur[j]);
				else 
					cur_cost = y * (cur[j] - want[i]);
				if (cur_cost < min_cost)
				{
					min_cost = cur_cost;
					min_index = j;
				}
			}
		output += min_cost;
		used[min_index] = 1;
	}
	fprintf(fout, "%d\n", output);
}