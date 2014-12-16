/*
 ID: arpon.r1
 PROG: fence
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int adjmatrix[500][500], nfences[500], tour[1025], tour_pos, min_node = 100000, max_node;

int cmp(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

void eulerian_tour(int i)
{
	//cout << "booyah!" << endl;
	for (int j = min_node; j <= max_node; j++)
		if (adjmatrix[i][j])
		{
			adjmatrix[i][j]--;
			adjmatrix[j][i]--;
			eulerian_tour(j);
		}
	tour[tour_pos++] = i;
}
int main()
{
	ofstream fout("fence.out");
	ifstream fin("fence.in");
	int F, i;
	fin >> F;
	for (i = 0; i < F; i++)
	{
		int n1, n2;
		fin >> n1 >> n2;
		adjmatrix[n1-1][n2-1]++;
		adjmatrix[n2-1][n1-1]++;
		nfences[n1-1]++;
		nfences[n2-1]++;
		if (n1 - 1 > max_node)
			max_node = n1 - 1;
		if (n2 - 1 > max_node)
			max_node = n2 - 1;
		if (n1 - 1 < min_node)
			min_node = n1 - 1;
		if (n2 - 1 < min_node)
			min_node = n2 - 1;
	}
	for (i = min_node; i <= max_node; i++)
		if (nfences[i] % 2 == 1)
			break;
	if (i > max_node)
		for (i = min_node; i <= max_node; i++)
			if (nfences[i])
				break;
	eulerian_tour(i);
	for (i = tour_pos - 1; i >= 0; i--)
		fout << tour[i] + 1 << endl;
}