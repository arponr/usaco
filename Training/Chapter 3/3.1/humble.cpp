/*
 ID: arpon.r1
 PROG: humble
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define INF 2147483647

int main()
{
	ofstream fout("humble.out");
	ifstream fin("humble.in");
	int i, j, n, k, cnt = 0;
	fin >> k >> n;
	int pfacts[k], minhums[k];
	long humbles[n + 1];
	for (i = 0; i < k; i++)
	{
		fin >> pfacts[i];
		minhums[i] = 0;
	}
	humbles[0] = 1;
	for (i = 1; i <= n; i++)
		humbles[i] = 0;
	while (cnt <= n)
	{
		long next_hum = INF;
		for (i = 0; i < k; i++)
			for (j = minhums[i]; humbles[j] > 0; j++)
				if (pfacts[i] * humbles[j] > humbles[cnt])
				{
					if (pfacts[i] * humbles[j] < next_hum)
						next_hum = pfacts[i] * humbles[j];
					minhums[i] = j;
					break;
				}
		humbles[++cnt] = next_hum;
	}
	fout << humbles[n] << endl;
}