#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,M; scanf("%d %d",&N,&M);
  vector<vector<int>> cubes(N,vector<int>(N,0));
  vector<vector<int>> A(N,vector<int>(N,0));
  for (int m=0;m<M;++m) {
    int r,c; scanf("%d %d",&r,&c); r--; c--;
    cubes[r][c] = 1;
  }
  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      if (i == 0 && j == 0)
        A[i][j] = cubes[i][j];
      else if (i == 0)
        A[i][j] = A[i][j-1] + cubes[i][j];
      else if(j == 0)
        A[i][j] = A[i-1][j] + cubes[i][j];
      else
        A[i][j] = A[i-1][j] + A[i][j-1] - A[i-1][j-1] + cubes[i][j];
    }
  }
  int best = 1000000;
  for (int l=0;l<N;++l) {
    for (int r=l;r<N;++r) {
      int w = r-l+1;
      if (M%w != 0) continue;
      if (w > M) continue;
      int h = M/w;
      for (int row=0;row<N-h+1;++row) {
        int amt;
        if (row == 0 && l == 0)
          amt = A[row+h-1][r];
        else if (row == 0)
          amt = A[row+h-1][r] - A[row+h-1][l-1];
        else if (l == 0)
          amt = A[row+h-1][r] - A[row-1][r];
        else
          amt = A[row+h-1][r] - A[row+h-1][l-1] - A[row-1][r] + A[row-1][l-1];
          
        best = min(best,M-amt);
      }
    }
  }
  cout << best << endl;
  return 0;
}