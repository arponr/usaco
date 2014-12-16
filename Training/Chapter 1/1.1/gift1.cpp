
/*
 ID: arpon.r1
 PROG: gift1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

int lookUp(string n, vector<string> &nms)
{
	for (int a = 0; a < nms.size(); a++)
		if (nms[a] == n)
			return a;
	return -1;
}

int main()
{
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");
	int numPpl;
	fin >> numPpl;
	vector<int> money(numPpl,0);
	vector<string> names(numPpl);
	for (int a = 0; a < numPpl; a++)
		fin >> names[a];
	for (int x = 0; x < numPpl; x++)
	{
		string giver, receiver;
		int mon, gifts;
		fin >> giver;
		fin >> mon >> gifts;
		if ((mon != 0) && (gifts != 0))
		{
			int divided = (int)floor(mon / gifts);
			money[lookUp(giver, names)] += (mon - divided * gifts) - mon;
			for (int y = 0; y < gifts; y++)
			{
				fin >> receiver;
				money[lookUp(receiver, names)] += divided;
			}
		}
	}
	for (int i = 0; i < numPpl; i++)
		fout << names[i] << " " << money[i] << endl;
	fout.close();
	exit(0);
	return 0;
	
}

