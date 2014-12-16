/*
 ID: arpon.r1
 PROG: spin
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

typedef struct wheel wheel;
struct wheel
{
	int speed, num_wedges, wedges[5], extent[5];
};

wheel wheels[5];
int angles[5][5][360];
int seconds_passed = 0, check = 0, min_i, min_j;

// min(min(min(a, b), c), min(d, e))
bool aligned()
{
	int a, b, c, d, e;
	for (a = 0; a < wheels[0].num_wedges; a++)
	{
		for (b = 0; b < wheels[1].num_wedges; b++)
		{
			for (c = 0; c < wheels[2].num_wedges; c++)
			{
				for (d = 0; d < wheels[3].num_wedges; d++)
				{
					for (e = 0; e < wheels[4].num_wedges; e++)
					{
						int whind = -1, weind = -1, correspond[5] = {a, b, c, d, e};
						if (wheels[0].extent[a] <= wheels[1].extent[b] && wheels[0].extent[a] <= wheels[2].extent[c] && wheels[0].extent[a] <= wheels[3].extent[d] && wheels[0].extent[a] <= wheels[4].extent[e])
						{
							whind = 0; 
							weind = a;
						}
						else if (wheels[1].extent[b] <= wheels[0].extent[a] && wheels[1].extent[b] <= wheels[2].extent[c] && wheels[1].extent[b] <= wheels[3].extent[d] && wheels[1].extent[b] <= wheels[4].extent[e])
						{
							whind = 1; 
							weind = b;
						}
						else if (wheels[2].extent[c] <= wheels[1].extent[b] && wheels[2].extent[c] <= wheels[0].extent[a] && wheels[2].extent[c] <= wheels[3].extent[d] && wheels[2].extent[c] <= wheels[4].extent[e])
						{
							whind = 2; 
							weind = c;
						}
						else if (wheels[3].extent[d] <= wheels[1].extent[b] && wheels[3].extent[d] <= wheels[2].extent[c] && wheels[3].extent[d] <= wheels[0].extent[a] && wheels[3].extent[d] <= wheels[4].extent[e])
						{
							whind = 3; 
							weind = d;
						}
						else if (wheels[4].extent[e] <= wheels[1].extent[b] && wheels[4].extent[e] <= wheels[2].extent[c] && wheels[4].extent[e] <= wheels[3].extent[d] && wheels[4].extent[e] <= wheels[0].extent[a])
						{
							whind = 4; 
							weind = e;
						}
						int i, j;
						for (i = 0; i < 5; i++)
						{
							if (i != whind)
							{
								for (j = 0; j <= wheels[whind].extent[weind]; j++)
									if (angles[i][correspond[i]][(wheels[whind].wedges[weind] + j) % 360] == seconds_passed)
										break;
								if (j > wheels[whind].extent[weind])
								{
									if (seconds_passed == 1)
										cout << i;
									break;
								}
							}
						}
						if (i == 5)
							return true;
					}
				}
			}
		}
	}
	return false;						
}

void rotate()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < wheels[i].num_wedges; j++)
		{
			wheels[i].wedges[j] = (wheels[i].wedges[j] + wheels[i].speed) % 360;
			for (int k = 0; k <= wheels[i].extent[j]; k++)
				angles[i][j][(wheels[i].wedges[j] + k) % 360] = seconds_passed + 1;
		}
	}
}

int main()
{
	ifstream fin("spin.in");
	ofstream fout("spin.out");
	int i, j, k;
	for (i = 0; i < 5; i++)
	{
		fin >> wheels[i].speed >> wheels[i].num_wedges;
		for (j = 0; j < wheels[i].num_wedges; j++)
		{
			fin >> wheels[i].wedges[j] >> wheels[i].extent[j];
			for (k = 0; k <= wheels[i].extent[j]; k++)
				angles[i][j][(wheels[i].wedges[j] + k) % 360] = 1;
		}
	}
	while (seconds_passed < 360)
	{
		seconds_passed++;
		if (aligned())
			break;
		rotate();
	}
	if (seconds_passed == 360)
		fout << "none" << endl;
	else
		fout << seconds_passed - 1<< endl;
}

