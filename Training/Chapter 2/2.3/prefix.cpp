/*
 ID: arpon.r1
 PROG: prefix
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string prims[200], seq;
int n = 0, len = 0;

int main()
{
	ofstream fout("prefix.out");
	ifstream fin("prefix.in");
	string temp;
	fin >> temp;
	while (temp != ".")
	{
		prims[n++] = temp;
		fin >> temp;
	}
	while(fin >> temp)
		seq += temp;
	bool prelen[seq.length() + 1];
	prelen[0] = 1;
	for (int x = 1; x <= seq.length(); x++)
		prelen[x] = 0;
	for (int i = 0; i <= seq.length(); i++)
	{
		if (prelen[i])
		{
			len = i;
			for (int j = 0; j < n; j++)
			{
				int k;
				for (k = 0; k < prims[j].length() && prims[j][k] == seq[i + k]; k++);
				if (k == prims[j].length())
					prelen[i + prims[j].length()] = 1;
			}
		}
	}
	fout << len << endl;
	return 0;
}
	