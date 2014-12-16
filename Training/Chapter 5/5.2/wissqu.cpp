/*
ID: arpon.r1
PROG: wissqu
LANG: C++
*/

#include <cstdio>
using namespace std;

FILE *fin = fopen ("wissqu.in", "r"), *fout = fopen ("wissqu.out", "w");

const int NTYPES = 5, MAX = 4;

int p [MAX][MAX], left [NTYPES] = {3, 3, 3, 4, 3}, near [MAX][MAX][NTYPES], 
	st [MAX * MAX][3], sol [MAX * MAX][3], nways = 0;
bool moved [MAX][MAX];

bool valid (int i, int j)
{
	return i >= 0 && i < MAX && j >= 0 && j < MAX;
}

void update (int i, int j, int herd, int add)
{
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
			if (valid (i + a, j + b))
				near [i + a][j + b][herd] += add;
}

void dfs (int depth)
{
	if (depth == MAX * MAX)
	{
		if (nways == 0)
			for (int i = 0; i < depth; i++)
				for (int j = 0; j < 3; j++)
					sol [i][j] = st [i][j];
		nways++;
	}
	else if (depth == 0)
	{
		int herd = 'D' - 'A';
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				if (!moved [i][j] && near [i][j][herd] == 0)
				{
					int tmp = p [i][j];
					p [i][j] = herd;
					update (i, j, herd, 1);
					update (i, j, tmp, -1);
					left [herd]--;
					moved [i][j] = true;
					st [depth][0] = herd; st [depth][1] = i; st [depth][2] = j;
					
					dfs (depth + 1);
					
					p [i][j] = tmp;
					update (i, j, herd, -1);
					update (i, j, tmp, 1);
					left [herd]++;
					moved [i][j] = false;
				}
	}
	else
	{
		for (int herd = 0; herd < NTYPES; herd++)
			if (left [herd] > 0)
				for (int i = 0; i < MAX; i++)
					for (int j = 0; j < MAX; j++)
						if (!moved [i][j] && near [i][j][herd] == 0)
						{
							int tmp = p [i][j];
							p [i][j] = herd;
							update (i, j, herd, 1);
							update (i, j, tmp, -1);
							left [herd]--;
							moved [i][j] = true;
							st [depth][0] = herd; st [depth][1] = i; st [depth][2] = j;
							
							dfs (depth + 1);
							
							p [i][j] = tmp;
							update (i, j, herd, -1);
							update (i, j, tmp, 1);
							left [herd]++;
							moved [i][j] = false;
						}
	}
}
	
int main ()
{	
	for (int i = 0; i < MAX; i++)
	{
		char tmp [MAX + 5];
		fscanf (fin, "%s", tmp);
		for (int j = 0; j < MAX; j++)
		{
			p [i][j] = tmp [j] - 'A';
			update (i, j, p [i][j], 1);
		}
	}
	
	dfs (0);
	
	for (int i = 0; i < MAX * MAX; i++)
		fprintf (fout, "%c %d %d\n", sol [i][0] + 'A', sol [i][1] + 1, sol [i][2] + 1);
	fprintf (fout, "%d\n", nways);
	
	return 0;
}