/*
 ID: arpon.r1
 PROG: fence8
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXB 50
#define MAXR 1023

int nboards, nrails,
	boards[MAXB], rails[MAXR],
	minboard[MAXR],
	boardsum, railsum[MAXR],
	goal, useless, allowed;

ofstream fout("fence8.out");	

int qcmp (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

void DFS (int rail, int start)
{
	int i;
	if (railsum[rail] > boardsum || useless > allowed)
		return;
	if (rail == 0)
	{
		for (i = start; i < nboards; i++)
			if (boards[i] >= rails[0])
			{
				goal++;
				break;
			}
		fout << goal << endl;
		exit(0);
	}
	for (i = start; i < nboards; i++)
	{
		if (boards[i] >= rails[rail])
		{
			boards[i] -= rails[rail];
			boardsum -= rails[rail];
			if (boards[i] < rails[0])
				useless += boards[i];
			if (rails[rail-1] == rails[rail])
				DFS(rail - 1, i);
			else
				DFS(rail - 1, minboard[rail-1]);
			if (boards[i] < rails[0])
				useless -= boards[i];
			boards[i] += rails[rail];
			boardsum += rails[rail];
		}
	}
}

int main()
{
	ifstream fin("fence8.in");
	int i, j;
	fin >> nboards;
	for (i = 0; i < nboards; i++)
	{
		fin >> boards[i];
		boardsum += boards[i];
	}
	fin >> nrails;
	for (i = 0; i < nrails; i++)
		fin >> rails[i];
	qsort(boards, nboards, sizeof(int), qcmp);
	qsort(rails, nrails, sizeof(int), qcmp);
	railsum[0] = rails[0];
	for (i = 1; i < nrails && railsum[i-1] <= boardsum; i++)
		railsum[i] = railsum[i-1] + rails[i];
	nrails = i - 1;
	for (i = 0; i <= nrails; i++)
	{
		for (j = 0; j < nboards; j++)
			if (boards[j] >= rails[i])
			{
				minboard[i] = j;
				break;
			}
		if (j == nboards)
		{
			nrails = i - 1;
			break;
		}
	}
	if (nrails == -1)
	{
		fout << 0 << endl;
		return 0;
	}
	for (i = nrails; i >= 0; i--)
	{
		goal = i;
		useless = 0;
		allowed = boardsum - railsum[i];
		DFS(i, minboard[i]);
	}
}