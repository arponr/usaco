/*
 ID: arpon.r1
 PROG: milk2
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<bool> times(1000000, false);
int early = 1000000, late = 0;

void addFarmer(int s, int e)
{
	for (int x = s; x <= e; x++)
	{
		times[x] = true;
	}
}

int cont()
{
	int count = 0, maxi = 0;
	for (int x = early; x < late; x++)
	{
		if (times[x] == true)
			count++;
		else
		{
			if (count > maxi)
				maxi = count;
			count = 0;
		}
	}
	if (count > maxi)
		maxi = count;
	return maxi;
}

int idle()
{
	int count = 0, maxi = 0;
	for (int x = early; x < late; x++)
	{
		if (times[x] == false)
			count++;
		else
		{
			if (count > maxi)
				maxi = count;
			count = 0;
		}
	}
	if (count > maxi)
		maxi = count;
	return maxi;
}
	
int main()
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		int start, end;
		fin >> start >> end;
		addFarmer(start, end - 1);
		if (start < early)
			early = start;
		if (end > late)
			late = end;
	}
	fout << cont() << " " << idle() << endl;
	fout.close();
	exit(0);
	return 0;
}