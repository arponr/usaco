/*
 ID: arpon.r1
 PROG: pprime
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout("pprime.out");
int a, b, end;

bool is_prime(int x)
{
	if (x == 2)
		return true;
	if (x == 1 || x % 2 == 0)
		return false;
	for (int a = 3; a * a <= x; a += 2)
		if (x % a == 0)
			return false;
	return true;
}

void search(int cur)
{
		if (cur > end)
			return;
		else if (cur == 1)
		{
			int stop;
			if (b > 9)
				stop = 9;
			else
				stop = b;
			for (int x = a; x <= stop; x++)
				if (is_prime(x))
					fout << x << endl;
		}
		else if (cur == 2)
		{
			for (int x = 1; x <= 9; x += 2)
				if (10 * x + x >= a && 10 * x + x <= b && is_prime(10 * x + x))
					fout << 10 * x + x << endl;
		}
		else if (cur == 3)
		{
			for (int x = 1; x <= 9; x += 2)
				for (int y = 0; y <= 9; y++)
					if (100 * x + 10 * y + x >= a && 100 * x + 10 * y + x <= b && is_prime(100 * x + 10 * y + x))
						fout << 100 * x + 10 * y + x << endl;
		}
		else if (cur == 5)
		{
			for (int x = 1; x <= 9; x += 2)
				for (int y = 0; y <= 9; y++)
					for (int z = 0; z <= 9; z++)
						if (10000 * x + 1000 * y + 100 * z + 10 * y + x >= a && 10000 * x + 1000 * y + 100 * z + 10 * y + x <= b && is_prime(10000 * x + 1000 * y + 100 * z + 10 * y + x))
							fout << 10000 * x + 1000 * y + 100 * z + 10 * y + x << endl;
		}
		else
		{
			for (int x = 1; x <= 9; x += 2)
				for (int y = 0; y <= 9; y++)
					for (int z = 0; z <= 9; z++)
						for (int w = 0; w <= 9; w++)
							if (1000000 * x + 100000 * y + 10000 * z + 1000 * w + 100 * z + 10 * y + x >= a && 1000000 * x + 100000 * y + 10000 * z + 1000 * w + 100 * z + 10 * y + x <= b && is_prime(1000000 * x + 100000 * y + 10000 * z + 1000 * w + 100 * z + 10 * y + x))
								fout << 1000000 * x + 100000 * y + 10000 * z + 1000 * w + 100 * z + 10 * y + x << endl;
		}
    if (cur == 1 || cur == 2)
		search(cur + 1);
	else
		search(cur + 2);
}
int main()
{
	ifstream fin("pprime.in");
	int n = 0, temp = 1, digitsA, digitsB;
	fin >> a >> b;
	while (a / temp > 0)
	{
		temp *= 10;
		n++;
	}
	digitsA = n;
	n = 0; temp = 1;
	while (b / temp > 0)
	{
		temp *= 10;
		n++;
	}
	digitsB = n;
	if (digitsA % 2 == 0 && digitsA != 2)
		digitsA++;
	if (digitsB % 2 == 0 && digitsB != 2)
		digitsB--;
	if (digitsB == 9)
		digitsB = 7;
	end = digitsB;
	search(digitsA);
	return 0;
}
