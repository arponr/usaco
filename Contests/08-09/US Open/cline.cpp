/*
ID: arpon.r1
PROB: cline
LANG: C++
*/

using namespace std;
#include <cstdio>
#define MID 100001

int arr[MID * 2], l = MID, r = MID;

int main()
{
	FILE *fin = fopen("cline.in", "r"), *fout = fopen("cline.out", "w");
	int s, i, k, n = 1;
	char a, b;
	fscanf(fin, "%d", &s);
	for (i = 0; i < s; i++)
	{
		fscanf(fin, " %c %c", &a, &b);
		if (a == 'A')
		{
			if (b == 'L')
				arr[--l] = n++;
			else
				arr[r++] = n++;
		}
		else
		{
			fscanf(fin, "%d", &k);
			if (b == 'L')
				l += k;
			else
				r -= k;
		}
	}
	for (i = l; i < r; i++)
		fprintf(fout, "%d\n", arr[i]);
}