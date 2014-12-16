/*
 ID: arpon.r1
 PROG: contact
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;
#define MAXLEN 12
#define MAXCOMB 4096

int counter[MAXLEN + 1][MAXCOMB + 1];
string sequence;

int value_of(string bitset)
{
	int i, out = 0;
	for (i = 0; i < bitset.length(); i++)
		out += ((int)bitset[i] - 48) << (bitset.length() - 1 - i);
	return out;
}

int main()
{
	ofstream fout("contact.out");
	ifstream fin("contact.in");
	int a, b, n, i, j, k;
	fin >> a >> b >> n;
	for (i = a; i <= b; i++)
		for (j = 0; j < (1 << i); j++)
			counter[i][j] = 0;
	while (fin.good())
	{
		string temp;
		fin >> temp;
		sequence += temp;
	}
	for (i = a; i <= b; i++)
		for (j = 0; j + i <= sequence.length(); j++)
			counter[i][value_of(sequence.substr(j, i))]++;
	for (k = 0; k < n; k++)
	{
		int maxcount = 0;
		for (i = a; i <= b; i++)
			for (j = 0; j < (1 << i); j++)
				if (counter[i][j] > maxcount)
					maxcount = counter[i][j];
		vector<string> out;
		for (i = a; i <= b; i++)
			for (j = 0; j < (1 << i); j++)
				if (counter[i][j] == maxcount)
				{
					bitset<16> b = j;
					string temp = b.to_string<char,char_traits<char>,allocator<char> >();
					out.push_back(temp.substr(temp.length() -  i, i));
					counter[i][j] = 0;
				}
		if (maxcount == 0)
			break;
		fout << maxcount << endl;
		int setcount = 0;
		for (j = 0; j < out.size() - 1; j++)
		{
			setcount++;
			if (setcount > 0 && setcount % 6 == 0)
			{
				setcount = 0;
				fout << out[j] << endl;
			}
			else
				fout << out[j] << " ";
		}
		fout << out[out.size() - 1] << endl;
	}
}