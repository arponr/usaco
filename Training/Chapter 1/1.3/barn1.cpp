/*
 ID: arpon.r1
 PROG: barn1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int compare (const void * a, const void * b)
{
	return *(int*)b - *(int*) a;
}


int main()
{
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");
	int m, s, c, low = 200, high = 0, count = 0, gapCount = 0;
	fin >> m >> s >> c;
	if (m < c)
	{
		bool stalls[s];
		int gaps[s];
		std::fill(gaps, gaps + s, 0);
		std::fill(stalls, stalls + s, false);
		for (int x = 0; x < c; x++)
		{
			int temp;
			fin >> temp;
			if (temp < low)
				low = temp;
			else if (temp > high)
				high = temp;
			stalls[temp - 1] = true;
		}
		for (int y = low - 1; y < high; y++)
		{
			if (!stalls[y])
				count++;
			else
			{
				gaps[gapCount++] = count;
				count = 0;
			}
		}
		qsort(gaps, gapCount, sizeof(int), compare);
		s = high - low + 1;
		for (int n = 0; n <  gapCount && n < m - 1; n++)
			s -= gaps[n];
		fout << s << endl;
	}
	else
		fout << c << endl;
	return 0;
}