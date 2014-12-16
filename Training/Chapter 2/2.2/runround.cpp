/*
 ID: arpon.r1
 PROG: runround
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
int pwrs[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int run_round(int num, int places)
{
	bool digits[10] = {false, false, false, false, false, false, false, false, false, false};
	int cur = 0,  x, orig;
	for (x = 0; x < places; x++)
	{
		int dig = (num / pwrs[places - cur - 1]) % 10;
		if (x == 0)
			orig = dig;
		digits[dig] = true;
		cur = (cur + dig) % places;
		dig = (num / pwrs[places - cur - 1]) % 10;
		if (x < places - 1 && digits[dig])
			break;
		else if (x == places - 1)
		{
			if (dig == orig)
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

int main()
{
	ofstream fout("runround.out");
	ifstream fin("runround.in");
	int start;
	fin >> start;
	int x = start + 1;
	while (!run_round(x, (int)log10(x) + 1))
		x++;
	fout << x << endl;
}
