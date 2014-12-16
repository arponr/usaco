/*
ID: arpon.r1
PROG: window
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("window.in", "r"), *fout = fopen ("window.out", "w");

const int MAXW = 26 + 26 + 10 + 5;

struct window
{
	int ind, x1, y1, x2, y2;
	bool alive;
	
	void init (int a, int b, int c, int d)
	{
		x1 = a; x2 = b;
		y1 = c; y2 = d;
		alive = true;
	}
	
	bool valid ()
	{
		return x1 < x2 && y1 < y2;
	}
};

window windows [MAXW];
int n;

int max (int a, int b)
{
	return (a > b) ? a : b;
}

int min (int a, int b)
{
	return (a < b) ? a : b;
}

int map (char ch)
{
	if (ch >= 'A' && ch <= 'Z') return ch - 'A';
	else if (ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
	else return ch - '0' + 52;
}

void f_t (int i)
{
	for (int k = 0; k < MAXW; k++)
		if (windows [k].alive && windows [k].ind < windows [i].ind)
			windows [k].ind++;
	
	windows [i].ind = 0;
}

void f_b (int i)
{
	for (int k = 0; k < MAXW; k++)
		if (windows [k].alive && windows [k].ind > windows [i].ind)
			windows [k].ind--;
	
	windows [i].ind = n - 1;
}

void f_d (char ch)
{
	int i = map (ch);
	
	f_b (i);
	windows [i].alive = false;
	
	n--;
}

void f_w (char ch, int x1, int y1, int x2, int y2)
{
	int i = map (ch);
	windows [i].ind = n++;
	
	f_t (i);
	windows [i].init (min (x1, x2), max (x1, x2), min (y1, y2), max (y1, y2));
}

bool overlap (window a, window b)
{
	return !(a.x2 <= b.x1 || a.x1 >= b.x2 || a.y2 <= b.y1 || a.y1 >= b.y2);
}

double area (window w)
{
	if (!w.valid ()) return 0.0;
	
	for (int i = 0; i < MAXW; i++)
		if (windows [i].alive && windows [i].ind < w.ind && overlap (w, windows [i]))
		{
			window a, b, c, d, t = windows [i];
			a.ind = b.ind = c.ind = d.ind = w.ind;
			
			a.init (w.x1, t.x1, w.y1, w.y2);
			b.init (max (w.x1, t.x1), min (w.x2, t.x2), t.y2, w.y2);
			c.init (t.x2, w.x2, w.y1, w.y2);
			d.init (max (w.x1, t.x1), min (w.x2, t.x2), w.y1, t.y1);
			
			return area (a) + area (b) + area (c) + area (d);
		}
	
	return (w.x2 - w.x1) * (w.y2 - w.y1);
}

void f_s (char ch)
{
	window w = windows [map (ch)];
	
	fprintf(fout, "%.3lf\n", 100.0 * (area (w) / ((w.x2 - w.x1) * (w.y2 - w.y1))));
}

int main ()
{
	for (int i = 0; i < MAXW; i++)
		windows [i].alive = false;
	
	char read [50];
	
	fscanf (fin, "%s", read);
	while (!feof (fin))
	{
		char ch = read [2];
		int a, b, c, d;
		
		if (read [0] == 'w')
		{
			sscanf (read + 4, "%d,%d,%d,%d", &a, &b, &c, &d);
			f_w (ch, a, b, c, d);
		}
		else if (read [0] == 't')
			f_t (map (ch));
		else if (read [0] == 'b')
			f_b (map (ch));
		else if (read [0] == 'd')
			f_d (ch);
		else if (read [0] == 's')
			f_s (ch);
		
		fscanf (fin, "%s", read);
	}
	
	return 0;
}
			
			
	
	
	
	
	