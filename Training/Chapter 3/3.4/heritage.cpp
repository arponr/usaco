/*
 ID: arpon.r1
 PROG: heritage
 LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ofstream fout("heritage.out");

void recurse(string in, string pre)
{
	if (in.length() == 1 || in.length() == 0)
	{
		fout << in;
		return;
	}
	int i;
	for (i = 0; in[i] != pre[0]; i++)
		;
	recurse(in.substr(0, i), pre.substr(1, i));
	recurse(in.substr(i+1), pre.substr(i+1)); 
	fout << pre[0];
}

int main()
{
	ifstream fin("heritage.in");
	string in, pre;
	fin >> in >> pre;
	recurse(in, pre);
	fout << endl;
}