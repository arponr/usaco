/*
 ID: arpon.r1
 PROG: sort3
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int main()
{
	ofstream fout("sort3.out");
	ifstream fin("sort3.in");
	int n, moves = 0, temp, temp2;
	fin >> n;
	int orig[n], sorted[n];
	for (int i = 0; i < n; i++)
	{
		fin >> orig[i];
		sorted[i] = orig[i];
	}
	qsort(sorted, n, sizeof(int), compare);
	for (int x = 0; x < n; x++)
	{
		if (orig[x] != sorted[x])
		{
			int y;
			if (orig[x] == 3 && sorted[x] == 1) 
			{
				for (y = n - 1; y >= 0; y--)
					if (orig[y] == sorted[x] && orig[y] != sorted[y])
					{
						temp = y;
						break;
					}
			}
			else
			{
				for (y = 0; y < n; y++)
					if (orig[y] == sorted[x] && orig[y] != sorted[y])
					{
						temp = y;
						break;
					}
			}
			temp2 = orig[x];
			orig[x] = orig[y];
			orig[y] = temp2;
			moves++;
		}
	}
	fout << moves << endl;
	return 0;
}
		

