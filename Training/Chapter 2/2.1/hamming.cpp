/*
 ID: arpon.r1
 PROG: hamming
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int n, b, d, stops[8] = {2, 4, 8, 16, 32, 64, 128, 256};
vector<int> solution;

int okay(int x, int y)
{
	int diffs = 0;
	for (int a = 0; a < b; a++)
	{
		if (( x & (1 << a)) != (y & (1 << a)))
			diffs++;
	}
	if (diffs < d)
		return 0;
	else
		return 1;
}

int main()
{
	ofstream fout("hamming.out");
	ifstream fin("hamming.in");
	fin >> n >> b >> d;
	for (int k = 0; k < stops[b-1]; k++)
	{
		solution.clear();
		solution.push_back(k);
		for (int i = k + 1; i < stops[b-1] && solution.size() < n; i++)
		{
			int j;
			for (j = 0; j < solution.size(); j++)
				if (!okay(solution[j], i))
					break;
			if (j == solution.size())
				solution.push_back(i);
		}
		if (solution.size() == n)
			break;
	}
	int z;
	for (z = 0; z < solution.size() - 1; z++)
	{
		if ((z + 1) % 10 == 0)
			fout << solution[z] << endl;
		else
			fout << solution[z] << " ";
	}
	fout << solution[z] << endl;
	return 0;
}
		