/*
 ID: arpon.r1
 PROG: checker
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int cnt = 0, n, printCount = 0;
ofstream fout("checker.out");
int col[13], d1[26], d2[26], cur[13];

void search(int row, int stop)
{
	if (row == n)
	{
		if (n > 6 && cur[0] <= n/2)
			cnt += 2;
		else
			cnt++;
		if (printCount++ < 3)
		{
			for (int i = 0; i < n - 1; i++)
				fout << cur[i] << " ";
			fout << cur[n - 1] << endl;
		}
		return;
	}
	for (int x = 0; x < stop; x++)
	{
		if (!col[x] && !d1[row - x + (n - 1)] && !d2[row + x])
		{
			col[x]++;
			d1[row - x + (n - 1)]++;
			d2[row + x]++;
			cur[row] = x + 1;
			search(row + 1, n);
			col[x]--;
			d1[row - x + (n - 1)]--;
			d2[row + x]--;
			cur[row] = 0;
		}
	}
}

int main()
{
	ifstream fin("checker.in");
	fin >> n;
	if (n > 6)
		search(0, (n + 1)/2);
	else
		search(0, n);
	fout << cnt << endl;
	return 0;
}