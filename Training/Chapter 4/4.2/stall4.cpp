/*
  ID : arpon.r1
  PROG: stall4
  LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXDATA 200
#define INF 100000000
int matrix[2 * MAXDATA + 2][2 * MAXDATA + 2],
   flow[2 * MAXDATA + 2], src[2 * MAXDATA + 2], visit[2 * MAXDATA + 2],
   N, M;

void check_matrix()
{
   for (int i = 0; i <= N + M + 2; i++)
   {
      for (int j = 0; j <= N + M + 1; j++)
	 cerr << matrix[i][j] << ' ';
      cerr << endl;
   }
}

int network_flow()
{
   int tflow = 0, mflow = 0, mloc = -1, pcap, i, cur, next;
   while (1)
   {
      for (i = 0; i <= N + M + 1; i++)
      {
	 flow[i] = visit[i] = 0;
	 src[i] = -1;
      }
      flow[0] = INF;
      while (1)
      {
	 mflow = 0;
	 mloc = -1;
	 for (i = 0; i <= N + M + 1; i++)
	    if (flow[i] > mflow && !visit[i])
	    {
	       mflow = flow[i];
	       mloc = i;
	    }
	 if (mloc == -1 || mloc == N + M + 1) 
	    break;
	 visit[mloc] = 1;
	 for (i = 0; i <= N + M + 1; i++)
	    if (matrix[mloc][i])
	       if (flow[i] < min(mflow, matrix[mloc][i]))
	       {
		  src[i] = mloc;
		  flow[i] = min(mflow, matrix[mloc][i]);
	       }
      }
      if (mloc == -1) 
	 break;
      pcap = flow[N + M + 1];
      tflow += pcap;
      cur = N + M + 1;
      while (cur != 0)
      {
	 next = src[cur];
	 matrix[next][cur] -= pcap;
	 matrix[cur][next] += pcap;
	 cur = next;
      } 
   }
   return tflow;
}

int main()
{
   ofstream fout("stall4.out");
   ifstream fin("stall4.in");
   int i, j, s, s_i;
   fin >> N >> M;
   for (i = 1; i <= N; i++)
   {
      fin >> s;
      matrix[0][i] = 1;
      for (j = 0; j < s; j++)
      {
	 fin >> s_i;
	 s_i += N;
	 matrix[i][s_i] = 1;
	 matrix[s_i][N + M + 1] = 1;
      }
   }
   //check_matrix();
   fout << network_flow() << endl;
}
