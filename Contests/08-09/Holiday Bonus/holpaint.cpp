/*
 ID: !cowlovers
 PROG: holpaint
 LANG: C++
 */

#include <cstdio>

using namespace std;

bool goal[50000][15], pic[50000][15];
int r, c, q, right_count = 0;
/*
int main()
{
	FILE *fin = fopen("holpaint.in", "r"), *fout = fopen("holpaint.out", "w");
	fscanf(fin, "%d %d %d\n", &r, &c, &q);
	int i, j;
	char throwaway;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			char temp1;
			fscanf(fin, "%c", &temp1);
			goal[i][j] = (temp1 > '0');
			if (!goal[i][j])
				right_count++;
		}
		fscanf(fin, "%c", &throwaway);
	}
	for (i = 0; i < q; i++)
	{
		int r1, r2, c1, c2, x;
		fscanf(fin, "%d %d %d %d %d", &r1, &r2, &c1, &c2, &x);
		for (int i = r1 - 1; i < r2; i++)
			for (int j = c1 - 1; j < c2; j++)
				if (pic[i][j] != x)
				{
					if (x == goal[i][j])
						right_count++;
					else
						right_count--;
					pic[i][j] = x;
				}
		fprintf(fout, "%d\n", right_count);
	}
}*/
	
