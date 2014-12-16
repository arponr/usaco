/*
 ID: arpon.r1
 PROG: rect1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Rect Rect;
struct Rect
{
	int llx, lly, urx, ury, height, width, color, area;
};

vector<Rect> rects;

Rect make(int llx, int lly, int urx, int ury, int color)
{
	Rect r;
	r.llx = llx; r.lly = lly; r.urx = urx; r.ury = ury;
	r.width = (urx > llx) ? (urx - llx) : (llx - urx);
	r.height = (ury > lly) ? (ury - lly) : (lly - ury);
	r.area = r.height * r.width;
	r.color = color;
	return r;
}

void update(int i)
{
	rects[i].width = (rects[i].urx > rects[i].llx) ? (rects[i].urx - rects[i].llx) : (rects[i].llx - rects[i].urx);
	rects[i].height = (rects[i].ury > rects[i].lly) ? (rects[i].ury - rects[i].lly) : (rects[i].lly - rects[i].ury);
	rects[i].area = rects[i].height * rects[i].width;
}

int overlap(Rect r1, Rect r2)
{
	if (r1.ury <= r2.lly || r1.lly >= r2.ury || r1.llx >= r2.urx || r1.urx <= r2.llx)
		return 0;
	return 1;
}

void place_rectangle(Rect r)
{
	vector<Rect> current;
	int num_before = rects.size();
	for (int i = 0; i < num_before; i++)
	{
		if (rects[i].color > 0 && overlap(r, rects[i]))
		{
			Rect cut;
			if (r.llx > rects[i].llx)
			{
				cut = rects[i]; 
				cut.urx = r.llx;
				rects.push_back(cut);
				rects[i].llx = r.llx;
			}
			if (r.urx < rects[i].urx)
			{
				cut = rects[i]; 
				cut.llx = r.urx;
				rects.push_back(cut);
				rects[i].urx = r.urx;
			}
			if (r.ury < rects[i].ury)
			{
				cut = rects[i];
				cut.lly = r.ury;
				rects.push_back(cut);
				rects[i].ury = r.ury;
			}
			if (r.lly > rects[i].lly)
			{
				cut = rects[i]; 
				cut.ury = r.lly;
				rects.push_back(cut);
				rects[i].lly = r.lly;
			}
			vector<Rect>::iterator it = rects.begin() + i;
			rects.erase(it);
			i--; num_before--;
		}
	}
	rects.push_back(r);
	for (int i = 0; i < rects.size(); i++)
		update(i);
}
int main()
{
	ofstream fout("rect1.out");
	ifstream fin("rect1.in");
	int i, j, a, b, n, high = 1;
	fin >> a >> b >> n;
	rects.push_back(make(0, 0, a, b, 1));
	for (i = 0; i < n; i++)
	{
		int llx, lly, urx, ury, color;
		fin >> llx >> lly >> urx >> ury >> color;
		if (color > high)
			high = color;
		place_rectangle(make(llx, lly, urx, ury, color));
	}
	for (i = 1; i <= high; i++)
	{
		int area = 0;
		for (j = 0; j < rects.size(); j++)
			if (rects[j].color == i)
				area += rects[j].area;
		if (area > 0)
			fout << i << " " << area << endl;
	}
}