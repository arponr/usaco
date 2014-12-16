/*
 ID: arpon.r1
 PROG: cowcycle
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define INF 100000000
#define EPS 1e-14

int nfront, nrear, f_range_start, f_range_end, r_range_start, r_range_end,
front[5], rear[10], best_front[5], best_rear[10];
double ratios[50], differences[50], min_variance = INF;

void calculate()
{
	if (front[nfront-1] * rear[nrear-1] < 3 * front[0] * rear[0]) return;
	int cnt = 0, i, j;
	double mean = 0.0, variance = 0.0;
	for (i = 0; i < nfront; i++)
		for (j = nrear - 1; j >= 0; j--)
			ratios[cnt++] = ((double) front[i]) / ((double) rear[j]);
	bool changed = 1;
	while (changed)
	{
		changed = 0;
		for (i = 0; i < cnt - 1; i++)
			if (ratios[i] > ratios[i+1])
			{
				double temp = ratios[i];
				ratios[i] = ratios[i+1];
				ratios[i+1] = temp;
				changed = 1;
			}
	}
	cnt--;
	for (i = 0; i < cnt; i++)
		differences[i] = ratios[i+1] - ratios[i];
	for (i = 0; i < cnt; i++)
		mean += differences[i];
	mean /= cnt;
	for (i = 0; i < cnt; i++)
		variance += (differences[i] - mean) * (differences[i] - mean);
	variance /= cnt;
	if (variance < min_variance)
	{
		min_variance = variance;
		for (i = 0; i < nfront; i++)
			best_front[i] = front[i];
		for (j = 0; j < nrear; j++)
			best_rear[j] = rear[j];
	}
}

void build_rear(int curr, int ngears)
{
	if (ngears == nrear)
	{
        calculate();
        return;
	}
	for (int i = curr; i <= r_range_end; i++)
	{
		rear[ngears] = i;
		build_rear(i + 1, ngears + 1);
	}
}

void build_front(int curr, int ngears)
{
	if (ngears == nfront)
	{
        build_rear(r_range_start, 0);
        return;
	}
	for (int i = curr; i <= f_range_end; i++)
	{
		front[ngears] = i;
		build_front(i + 1, ngears + 1);
	}
}

int main()
{
    ofstream fout("cowcycle.out");
    ifstream fin("cowcycle.in");
    int i;
    fin >> nfront >> nrear >> f_range_start >> f_range_end >> r_range_start >> r_range_end;
    build_front(f_range_start, 0);
    fout << best_front[0];
    for (i = 1; i < nfront; i++)
        fout << ' ' << best_front[i];
    fout << endl << best_rear[0];
    for (i = 1; i < nrear; i++)
        fout << ' ' << best_rear[i];
    fout << endl;
}
