/*
 ID: arpon.r1
 PROG: bullcow
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MOD 5000011
#define MAXN 100000

int N, K;

int main()
{
	ofstream fout("bullcow.out");
	ifstream fin("bullcow.in");
	int i, j;
	fin >> N >> K;
	int output = 1 + N;
	for (i = 0; i + K + 1 < N; i++)
	{
		int intermediates[MAXN * 2], temp;
		intermediates[0] = 1;
		for (j = 1; i + j * (K + 1) < N; j++)
		{
			if (j == 1) temp = N - (i + 1);
			else temp = intermediates[j-1];
			intermediates[j] = (intermediates[j-1] * ((temp - K) * (temp - K + 1) / 2)) % MOD;
			output = (output + intermediates[j]) % MOD;
		}
	}
	fout << output << endl;
}