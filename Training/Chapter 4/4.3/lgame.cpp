/*
 ID: arpon.r1
 PROG: lgame
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define NUMLTRS 26
#define MAXLEN 7
#define MAXANSWERS 5000
struct trie_node
{
	int complete;
	struct trie_node *next[NUMLTRS];
};

struct trie_node *root = (struct trie_node *) malloc(sizeof(struct trie_node));

int ltr_vals[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7},
	available[26], len,
	best, num_best;

char word[MAXLEN + 3], output[MAXANSWERS][MAXLEN + 3];

struct trie_node * make_node()
{
	struct trie_node *t = (struct trie_node *) malloc(sizeof(struct trie_node));
	memset(t->next, NULL, sizeof(t->next));
	t->complete = 0;
	return t;
}

void add_word(char *str)
{
	struct trie_node *t = root;
	char *p;
	int char_val;
	for (p = str; *p; p++)
	{
		char_val = *p - 'a';
		if (t->next[char_val] == NULL)
			t->next[char_val] = make_node();
		t = t->next[char_val];
	}
	t->complete = 1;
}

int lookup_word(char *str)
{
	struct trie_node *t = root;
	char *p;
	int char_val;
	for (p = str; *p; p++)
	{
		char_val = *p - 'a';
		if (t->next[char_val] == NULL)
			return 0;
		t = t->next[char_val];
	}
	return (t->complete || t == root);
}

int str_sort (const void * a, const void * b)
{
	return (strcmp((char*)a, (char*)b));
}

int get_score(char *str)
{
	char *p;
	int score = 0;
	for (p = str; *p; p++)
		score += ltr_vals[*p - 'a'];
	return score;
}

int special_equal(char *a, char *b, char *c)
{
	char d[MAXLEN + 3], e[MAXLEN + 3], *p;
	int d_len = 0, e_len = 0;
	for (p = c; *p != ' '; p++)
		d[d_len++] = *p;
	d[d_len] = '\0';
	for (p++; *p; p++)
		e[e_len++] = *p;
	e[e_len] = '\0';
	if (strcmp(a, d) == 0 && strcmp(b, e) == 0)
		return 1;
	if (strcmp(a, e) == 0 && strcmp(b, d) == 0)
		return 1;
	return 0;
}

void build_word(int depth)
{
	int i, j;
	if (depth >= 3)
	{
		int split1, split2;
		char a[MAXLEN + 1], b[MAXLEN + 1];
		for (i = 0; i <= depth  - 3; i++)
		{
			split1 = depth - i; 
			split2 = i;
			for (j = 0; j < split1; j++)
				a[j] = word[j];
			a[split1] = '\0';
			for (j = 0; j < split2; j++)
				b[j] = word[split1 + j];
			b[split2] = '\0';
			bool a_good = lookup_word(a), b_good = lookup_word(b);
			if (a_good && b_good && a[0] && b[0])
			{
				if (get_score(a) + get_score(b) == best)
				{
					for (j = 0; j < num_best; j++)
						if (special_equal(a, b, output[j]))
							break;
					if (j == num_best)
					{
						int pl, pl2;
						for (pl = 0; pl < split1; pl++)
							output[num_best][pl] = a[pl];
						output[num_best][pl++] = ' ';
						for (pl2 = 0; pl2 < split2; pl2++)
							output[num_best][pl + pl2] = b[pl2];
						num_best++;
					}
				}
				else if (get_score(a) + get_score(b) > best)
				{
					best = get_score(a) + get_score(b);
					num_best = 0;
					int pl, pl2;
					for (pl = 0; pl < split1; pl++)
						output[num_best][pl] = a[pl];
					output[num_best][pl++] = ' ';
					for (pl2 = 0; pl2 < split2; pl2++)
						output[num_best][pl + pl2] = b[pl2];
					num_best++;
				}
			}
			else if (a_good)
			{
				if (get_score(a) == best)
				{
					for (j = 0; j < num_best; j++)
						if (strcmp(output[j], a) == 0)
							break;
					if (j == num_best)
						strcpy(output[num_best++], a);
				}
				else if (get_score(a) > best)
				{
					best = get_score(a);
					num_best = 0;
					strcpy(output[num_best++], a);
				}
			}
			else if (b_good)
			{
				if (get_score(b) == best)
				{
					for (j = 0; j < num_best; j++)
						if (strcmp(output[j], b) == 0)
							break;
					if (j == num_best)
						strcpy(output[num_best++], b);
				}
				else if (get_score(b) > best)
				{
					best = get_score(b);
					num_best = 0;
					strcpy(output[num_best++], b);
				}
			}
		}
	}
	if (depth < len)
	{
		for (i = 0; i < NUMLTRS; i++)
			if (available[i])
			{
				available[i]--;
				word[depth] = 'a' + i;
				build_word(depth + 1);
				available[i]++;
			}
	}
}

int main()
{
	ofstream fout("lgame.out");
	ifstream fin("lgame.in"), dict("lgame.dict");
	char dict_in[MAXLEN], file_in;
	while (fin >> file_in)
	{
		len++;
		available[file_in - 'a']++;
	}
	dict.getline(dict_in, MAXLEN + 1);
	while (dict_in[0] != '.')
	{
		add_word(dict_in);
		dict.getline(dict_in, MAXLEN + 1);
	}
	build_word(0);
	fout << best << endl;
	qsort(output, num_best, sizeof(char[10]), str_sort);
	for (int i = 0; i < num_best; i++)
		fout << output[i] << endl;
}