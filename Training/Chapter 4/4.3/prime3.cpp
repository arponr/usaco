/*
 ID: arpon.r1
 PROG: prime3
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MAXPRIMES 5000
#define MAXSOLS 250
#define NDIGITS 10
#define FIVESTART 10000
#define FIVEEND 99999

typedef struct prime PRIME;
struct prime
{
	int num, d[5];
};

typedef struct square SQUARE;
struct square
{
	int sq[5][5]; 
};

typedef struct list200 LIST200;
struct list200
{
	int n;
	PRIME l[200];
};

typedef struct list50 LIST50;
struct list50
{
	int n;
	PRIME l[50];
};

typedef struct list25 LIST25;
struct list25
{
	int n;
	PRIME l[25];
};

int up_left, row_sum, nprimes, nsols;
bool pat0[NDIGITS][NDIGITS][NDIGITS][NDIGITS][NDIGITS];
LIST200 pat1[NDIGITS], pat2[NDIGITS];
LIST50 pat3[NDIGITS][NDIGITS];
LIST25 pat4[NDIGITS][NDIGITS][NDIGITS], pat5[NDIGITS][NDIGITS][NDIGITS], pat6[NDIGITS][NDIGITS][NDIGITS];
SQUARE sols[MAXSOLS];

PRIME make_pr(int num)
{
	PRIME p;
	p.num = num;
	p.d[0] = num / 10000;
	p.d[1] = (num / 1000) % 10;
	p.d[2] = (num / 100) % 10;
	p.d[3] = (num / 10) % 10;
	p.d[4] = num % 10;
	return p;
}

void list_primes()
{
	int i, j, digit_sum;
	for (i = FIVESTART; i <= FIVEEND; i++)
	{
		for (j = 2; j * j <= i; j++)
			if (i % j == 0)
				break;
		if (j * j > i)
		{
			digit_sum = ((i / 10000) + ((i / 1000) % 10) + ((i / 100) % 10) + ((i / 10) % 10) + (i % 10));
			if (digit_sum == row_sum)
			{
				PRIME tmp = make_pr(i);
				pat0[tmp.d[0]][tmp.d[1]][tmp.d[2]][tmp.d[3]][tmp.d[4]] = 1;
				pat1[tmp.d[0]].l[pat1[tmp.d[0]].n++] = tmp;
				if (tmp.d[0] == 1 || tmp.d[0] == 3 || tmp.d[0] == 7 || tmp.d[0] == 9)
					pat2[tmp.d[2]].l[pat2[tmp.d[2]].n++] = tmp;
				if (tmp.d[1] != 0 && tmp.d[2] != 0 && tmp.d[3] != 0)
					pat3[tmp.d[0]][tmp.d[4]].l[pat3[tmp.d[0]][tmp.d[4]].n++] = tmp;
				pat4[tmp.d[0]][tmp.d[1]][tmp.d[3]].l[pat4[tmp.d[0]][tmp.d[1]][tmp.d[3]].n++] = tmp;
				pat5[tmp.d[0]][tmp.d[2]][tmp.d[4]].l[pat5[tmp.d[0]][tmp.d[2]][tmp.d[4]].n++] = tmp;
				pat6[tmp.d[1]][tmp.d[2]][tmp.d[3]].l[pat6[tmp.d[1]][tmp.d[2]][tmp.d[3]].n++] = tmp;
			}
		}
	}
}

void fill_square()
{
	int a, b, c, d, e, f, g, h, i;
	SQUARE grid;
	grid.sq[0][0] = up_left;
	for (a = 0; a < pat1[up_left].n; a++)
	{
		for (i = 1; i < 5; i++)
			grid.sq[i][i] = pat1[up_left].l[a].d[i];
		for (b = 0; b < pat2[grid.sq[2][2]].n; b++)
		{
			for (i = 0; i < 5; i++)
				grid.sq[4-i][i] = pat2[grid.sq[2][2]].l[b].d[i];
			for (c = 0; c < pat3[up_left][grid.sq[0][4]].n; c++)
			{
				for (i = 1; i < 4; i++)
					grid.sq[0][i] = pat3[up_left][grid.sq[0][4]].l[c].d[i];
				for (d = 0; d < pat4[grid.sq[0][1]][grid.sq[1][1]][grid.sq[3][1]].n; d++)
				{
					grid.sq[2][1] = pat4[grid.sq[0][1]][grid.sq[1][1]][grid.sq[3][1]].l[d].d[2];
					grid.sq[4][1] = pat4[grid.sq[0][1]][grid.sq[1][1]][grid.sq[3][1]].l[d].d[4];
					for (e = 0; e < pat4[grid.sq[0][3]][grid.sq[1][3]][grid.sq[3][3]].n; e++)
					{
						grid.sq[2][3] = pat4[grid.sq[0][3]][grid.sq[1][3]][grid.sq[3][3]].l[e].d[2];
						grid.sq[4][3] = pat4[grid.sq[0][3]][grid.sq[1][3]][grid.sq[3][3]].l[e].d[4];
						grid.sq[4][2] = row_sum - grid.sq[4][0] - grid.sq[4][1] - grid.sq[4][3] - grid.sq[4][4];
						if ((grid.sq[4][2] != 1 && grid.sq[4][2] != 3 && grid.sq[4][2] != 7 && grid.sq[4][2] != 9) || !pat0[grid.sq[4][0]][grid.sq[4][1]][grid.sq[4][2]][grid.sq[4][3]][grid.sq[4][4]])
							continue;
						for (f = 0; f < pat5[grid.sq[0][2]][grid.sq[2][2]][grid.sq[4][2]].n; f++)
						{
							grid.sq[1][2] = pat5[grid.sq[0][2]][grid.sq[2][2]][grid.sq[4][2]].l[f].d[1];
							grid.sq[3][2] = pat5[grid.sq[0][2]][grid.sq[2][2]][grid.sq[4][2]].l[f].d[3];
							for (g = 0; g < pat6[grid.sq[1][1]][grid.sq[1][2]][grid.sq[1][3]].n; g++)
							{
								grid.sq[1][0] = pat6[grid.sq[1][1]][grid.sq[1][2]][grid.sq[1][3]].l[g].d[0];
								grid.sq[1][4] = pat6[grid.sq[1][1]][grid.sq[1][2]][grid.sq[1][3]].l[g].d[4];
								for (h = 0; h < pat6[grid.sq[2][1]][grid.sq[2][2]][grid.sq[2][3]].n; h++)
								{
									grid.sq[2][0] = pat6[grid.sq[2][1]][grid.sq[2][2]][grid.sq[2][3]].l[h].d[0];
									grid.sq[2][4] = pat6[grid.sq[2][1]][grid.sq[2][2]][grid.sq[2][3]].l[h].d[4];
									grid.sq[3][0] = row_sum - grid.sq[0][0] - grid.sq[1][0] - grid.sq[2][0] - grid.sq[4][0];
									grid.sq[3][4] = row_sum - grid.sq[0][4] - grid.sq[1][4] - grid.sq[2][4] - grid.sq[4][4];
									if (grid.sq[3][0] >= 0 && grid.sq[3][0] < 10 && (grid.sq[3][4] == 1 || grid.sq[3][4] == 3 || grid.sq[3][4] == 7 || grid.sq[3][4] == 9))
									{
										/*for (int j = 0; j < 5; j++)
										{
											for (int k = 0; k < 5; k++)
												cout << grid.sq[j][k];
											cout << endl;
										}
										cout << endl;*/
										if (pat0[grid.sq[3][0]][grid.sq[3][1]][grid.sq[3][2]][grid.sq[3][3]][grid.sq[3][4]] && pat0[grid.sq[0][0]][grid.sq[1][0]][grid.sq[2][0]][grid.sq[3][0]][grid.sq[4][0]] && pat0[grid.sq[0][4]][grid.sq[1][4]][grid.sq[2][4]][grid.sq[3][4]][grid.sq[4][4]])
											sols[nsols++] = grid;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int sq_cmp(const void * a, const void * b)
{
	SQUARE *sq1 = (SQUARE*)a, *sq2 = (SQUARE*)b;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (sq1->sq[i][j] > sq2->sq[i][j])
				return 1;
			else if (sq1->sq[i][j] < sq2->sq[i][j])
				return -1;
	return 0;
}

int main()
{
	ofstream fout("prime3.out");
	ifstream fin("prime3.in");
	fin >> row_sum >> up_left;
	list_primes();
	fill_square();
	qsort(sols, nsols, sizeof(SQUARE), sq_cmp);
	if (nsols == 0)
		fout << "NONE" << endl;
	for (int i = 0; i < nsols; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
				fout << sols[i].sq[j][k];
			fout << endl;
		}
		if (i < nsols - 1)
			fout << endl;
	}
}
