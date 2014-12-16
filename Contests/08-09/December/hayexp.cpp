/*
 ID: arpon.r1
 PROG: hayexp
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("hayexp.out");
	ifstream fin("hayexp.in");
	int N, Q;
	fin >> N >> Q;
	int bales[N];
	for (int i = 0; i < N; i++)
		fin >> bales[i];
	for (int j = 0; j < Q; j++)
	{
		int start, end, sum = 0;
		fin >> start >> end;
		for (int x = start - 1; x < end; x++)
			sum += bales[x];
		fout << sum << endl;
	}
	return 0;
}
