/*
 ID: arpon.r1
 PROG: buylow
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MAXDAYS 5000
#define BASE 100000000
#define DATASIZE 15

struct big_int
{
	int size, data[DATASIZE];
};

int ndays, prices[MAXDAYS],
	kitty[MAXDAYS];
	/* Descriptive variable names, shmescriptive variable names,
	   Nobody REALLY cares what the DP array is called, am I right?
	   Creativity defines this array, it just shouts, "PET ME!" */
	   
struct big_int num_seq[MAXDAYS];

void init_big_int(struct big_int *b, int val)
{
	b->size = 0;
	b->data[0] = val;
	for (int i = 1; i < DATASIZE; i++)
		b->data[i] = 0;
}

void add(struct big_int *a, struct big_int *b)
{
	int max_size = (a->size > b->size) ? a->size : b->size, carry = 0, i;
	for (i = 0; i <= max_size; i++)
	{
		a->data[i] += b->data[i] + carry;
		carry = a->data[i] / BASE;
		a->data[i] %= BASE;
	}
	if (carry)
		a->data[++max_size] = carry;
	a->size = max_size;
}

int main()
{
	ofstream fout("buylow.out");
	ifstream fin("buylow.in");
	int i, j, kitty_value, max_kitty = 0, last;
	struct big_int output;
	fin >> ndays;
	for (i = 0; i < ndays; i++)
		fin >> prices[i];
	for (i = 0; i < ndays; i++)
	{
		kitty_value = 1;
		for (j = i - 1; j >= 0; j--)
			if (prices[i] < prices[j] && kitty[j] + 1 > kitty_value)
				kitty_value = kitty[j] + 1;
		kitty[i] = kitty_value;
		if (kitty_value > max_kitty)
			max_kitty = kitty_value;
	}
	for (i = 0; i < ndays; i++)
		if (kitty[i] == 1)
			init_big_int(&num_seq[i], 1);
		else
		{
			init_big_int(&num_seq[i], 0);
			last = -1;
			for (j = i - 1; j >= 0; j--)
				if (prices[i] < prices[j] && kitty[j] == kitty[i] - 1 && prices[j] != last)
				{
					add(&num_seq[i], &num_seq[j]);
					last = prices[j];
				}
		}
	init_big_int(&output, 0);
	last = -1;
	for (i = ndays - 1; i >= 0; i--)
		if (kitty[i] == max_kitty && prices[i] != last)
		{
			add(&output, &num_seq[i]);
			last = prices[i];
		}
	fout << max_kitty << ' ';
	for (i = output.size; i >= 0; i--)
		fout << output.data[i];
	fout << endl;
}
	
