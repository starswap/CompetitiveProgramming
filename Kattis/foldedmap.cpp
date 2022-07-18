#include <bits/stdc++.h>
using namespace std;
int A_r,A_c,T_r,T_c;
vector<vector<int>> A;
vector<vector<int>> mapp;

int getAmount(int tlcR,int tlcC) {
  int brcR = tlcR+T_r-1;
  int brcC = tlcC+T_c-1;
  if (tlcR < 0)
    tlcR = 0;
  if (tlcC < 0)
    tlcC = 0;
  if (tlcR >= A_r)
    return 0;
  if (tlcC >= A_c)
    return 0;  
  if (brcR < 0)
    return 0;
  if (brcC < 0)
    return 0;
  if (brcR >= A_r)
    brcR = A_r-1;
  if (brcC >= A_c)
    brcC = A_c-1;

  if (tlcC == 0 && tlcR == 0)
    return A[brcR][brcC];    
  else if (tlcC == 0)
    return A[brcR][brcC] - A[tlcR-1][brcC];    
  else if (tlcR == 0)
    return A[brcR][brcC] - A[brcR][tlcC-1];
  else
    return A[brcR][brcC] - A[brcR][tlcC-1] - A[tlcR-1][brcC] + A[tlcR-1][tlcC-1];
}

int checkTiles(int tlcR,int tlcC) {
  int dx = 0;
  int total = 0;

  while (tlcC+dx*T_c < A_c) { //while top left corner of this tile is still on page.
    total += (getAmount(tlcR,tlcC+dx*T_c) > 0);
    dx++;
  };
  dx = 1;
  while (tlcC-dx*T_c+T_c-1 >= 0) { //while botton right corner of this tile is still on page.
    total += (getAmount(tlcR,tlcC-dx*T_c) > 0);
    dx++;
  }
  if (total == 0) //reached top.
    return 0;
  else
    return (total + checkTiles(tlcR-T_r,tlcC));
}


int main() {
  while (scanf("%d %d %d %d",&A_r,&A_c,&T_r,&T_c) != EOF) {
    A.assign(A_r,vector<int>(A_c,0));
    mapp.assign(A_r,vector<int>(A_c,0));
    string s;
    int rL,cL;
    for (int r=0;r<A_r;++r) {
      cin >> s;
      int total = 0;
      for (int c=0;c<A_c;++c) {
        mapp[r][c] = (s[c] == 'X');
        total += mapp[r][c];
        A[r][c] = ((r > 0) ? A[r-1][c] : 0) + total;
        if (s[c] == 'X') {
          rL = r;
          cL = c;
        }
      }
    }

    int best = 1000000000;
    for (int i=0;i<T_r;++i) {
      for (int j=0;j<T_c;++j) {
        best = min(best,checkTiles(rL-i,cL-j));
      }      
    }
    cout << best << endl;    
  }
  return 0;
}