/*
 ID: arpon.r1
 PROG: cryptcow
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef struct hash_ent hash_ent;
struct hash_ent
{
	char data[76];
	struct hash_ent *next;
};

#define MAXLEN 75
#define MOD 549149
#define MAXENTS 135000

int nxt[MAXLEN], len, head, num_encrypts, entries, goalltr[53], msgltr[53], begins[53][10], begincnts[53];

struct hash_ent *hash_t[MOD];

char message[MAXLEN], check[48] = "Begin the Escape execution at the Break of Dawn", out[MAXLEN + 1];

ofstream fout("cryptcow.out");

inline void to_str()
{
	int i, j;
	char *p;
	for (p = message + head, i = head, j = 0; i != -1; p = message + nxt[i], i = nxt[i], j++)
		out[j] = *p;
	out[j] = '\0';
}

inline int hash()
{
	char *p; int sum = 0;
	for (p = out; *p; p++)
		sum = (sum * 2243 + *p) % MOD;
	return sum;
}

inline void hash_insert(int val)
{
	struct hash_ent *h = (struct hash_ent *) malloc(sizeof(struct hash_ent));
	strcpy(h->data, out);
	h->next = hash_t[val];
	hash_t[val] = h;
}

int hash_lookup()
{
	struct hash_ent *h;
	to_str();
	int val = hash();
	char *p, *q;
	for (h = hash_t[val]; h; h = h->next)
	{
		for (p = h->data, q = out; *p && *q; p++, q++)
			if (*p != *q)
				break;
		if (!*p && !*q) return 1;
	}
	if (entries++ < MAXENTS)
		hash_insert(val);
	return 0;
}

int check_ltrs()
{
	char *p;
	int i, j;
	for (p = message; *p; p++)
	{
		if (*p == ' ') i = 52;
		else if (*p >= 'a') i = 26 + (*p - 'a');
		else i = *p - 'A';
		msgltr[i]++;
	}
	for (j = 0, p = check; *p; p++, j++)
	{
		if (*p == ' ') i = 52;
		else if (*p >= 'a') i = 26 + (*p - 'a');
		else i = *p - 'A';
		msgltr[i]--;
		begins[i][begincnts[i]++] = j;
	}
	msgltr[2] = msgltr[14] = msgltr[22] = 0;
	for (i = 0; i <= 52; i++)
		if (msgltr[i] != 0)
			return 0;
	return 1;
}

int check_substrs()
{
	char *p, *q, *r, *s;
	p = out; q = check;
	while (*p != 'C' && *p != 'O' && *p != 'W' && *p)
	{
		if (*p != *q)
			return 0;
		p++;
		q++;
	}
	if (!*p)
	{
		fout << 1 << " " << num_encrypts << endl;
		exit(0);
	}
	if (*p && *p != 'C')
		return 0;
	for (p++; *p; p++)
		if (*p != 'C' && *p != 'O' && *p != 'W')
		{
			int val, i;
			if (*p == ' ') val = 52;
			else if (*p >= 'a') val = 26 + (*p - 'a');
			else val = *p - 'A';
			for (i = 0; i < begincnts[val]; i++)
			{
				for (r = p + 1, s = check + begins[val][i] + 1; *r && *r != 'C' && *r != 'O' && *r != 'W' && *s; r++, s++)
					if (*r != *s)
						break;
				if (*r == 'C' || *r == 'O' || *r == 'W')
				{
					p = r + 1;
					break;
				}
				if (!*r)
				{
					p = out + strlen(out); q = check + 47;
					while (*p != 'C' && *p != 'O' && *p != 'W' && *p)
					{
						if (*p != *q)
							return 0;
						p--;
						q--;
					}
					return (!*p || *p == 'W');
				}
			}
			if (i == begincnts[val]) 
				return 0;
		}
	return 1;
}

void decrypt(int bc, int c, int bo, int o, int bw, int w)
{
	int temp;
	if (nxt[c] == o)
	{
		if (nxt[o] == w)
			temp = nxt[w];
		else
		{
			temp = nxt[o];
			nxt[bw] = nxt[w];
		}
	}
	else
	{
		if (nxt[o] == w)
		{
			temp = nxt[c];
			nxt[bo] = nxt[w];
		}
		else
		{
			temp = nxt[o];
			nxt[bw] = nxt[c];
			nxt[bo] = nxt[w];
		}
	}
	if (bc == -1)
		head = temp;
	else
		nxt[bc] = temp;
}

void print_str()
{
	for (int i = head; i != -1; i = nxt[i])
		cout << message[i];
	cout << endl;
}

void DFS(int depth)
{	
	int befc[depth], befo[depth], befw[depth],
	cind[depth], oind[depth], wind[depth],
	cord[depth], oord[depth], word[depth],
	ccnt = 0, ocnt = 0, wcnt = 0, i, j, k = -1;
	
	for (i = head, j = 0; i != -1; i = nxt[i], j++)
	{
		if (message[i] == 'C')
		{
			cind[ccnt] = i;
			cord[ccnt] = j;
			befc[ccnt++] = k;
		}
		else if (message[i] == 'O')
		{
			oind[ocnt] = i;
			oord[ocnt] = j;
			befo[ocnt++] = k;
		}
		else if (message[i] == 'W')
		{
			wind[wcnt] = i;
			word[wcnt] = j;
			befw[wcnt++] = k;
		}
		k = i;
	}
	
	for (i = 0; i < ccnt; i++)
		if (message[befc[i]] != 'C')
			for (j = 0; j < ocnt; j++)
				if (cord[i] < oord[j])
					for (k = 0; k < wcnt; k++)
						if (oord[j] < word[k])
						{
							decrypt(befc[i], cind[i], befo[j], oind[j], befw[k], wind[k]);
							to_str();
							if (check_substrs() && !hash_lookup())
								DFS(depth - 1);
							if (befc[i] == -1)
								head = cind[i];
							else
								nxt[befc[i]] = cind[i];
							nxt[befo[j]] = oind[j];
							nxt[befw[k]] = wind[k];
						}
}

int main()
{
	ifstream fin("cryptcow.in");
	int i, cc = 0, oc = 0, wc = 0;
	char *p;
	fin.getline(message, 76);
	len = strlen(message);
	for (i = 0; i < len - 1; i++)
		nxt[i] = i + 1;
	nxt[len-1] = -1;
	for (p = message; *p; p++)
		if (*p == 'C') cc++;
		else if (*p == 'O') oc++;
		else if (*p == 'W') wc++;
	to_str();
	if (len - (cc + oc + wc) != 47 || (cc + oc + wc) % 3 != 0 || cc != oc || cc != wc || oc != wc || !check_ltrs() || !check_substrs())
	{
		fout << 0 << " " << 0 << endl;
		return 0;
	}
	num_encrypts = cc;
	head = 0;
	DFS(num_encrypts);
	fout << 0 << " " << 0 << endl;
}