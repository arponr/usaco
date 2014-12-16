
/*
 ID: arpon.r1
 PROG: beads
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
string beads;
int numBeads;

string reverse(string i)
{
	string output = "";
	string::reverse_iterator rit;
	for (rit = i.rbegin(); rit < i.rend(); rit++)
		output += *rit;
	return output;
}

int collect (int index, int dir)
{
	string orig = beads;
	beads = orig.substr(index) + orig.substr(0, index);
	if (dir == -1)
		beads = reverse(beads);
	char bead1 = beads.at(0);
	int count = 0;
	index = 0;
	while (bead1 == 'w')
	{
		count++;
		index++;
		if (index == numBeads)
			return numBeads;
		bead1 = beads.at(index);
	}
	for (; index < numBeads; index++)
	{
		if (beads.at(index) == bead1 || beads.at(index) == 'w')
			count++;
		else
			break;
	}
	beads = orig;
	return count;
}

int main()
{
	ofstream fout("beads.out");
	ifstream fin("beads.in");
	fin >> numBeads >> beads;
	int max;
	for (int x = 0; x < numBeads; x++)
	{
		if (collect(x, 1) + collect(x, -1) > max)
		{
			max = collect(x,1) + collect(x, -1);
			if (max >= numBeads)
			{
				max = numBeads;
				break;
			}
		}
	}
	fout << max << endl;
	fout.close();
	exit(0);
	return 0;
}
	

	