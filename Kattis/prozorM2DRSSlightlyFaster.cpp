//Since we have fixed size boxes this should be the best we can do. Although this is a max 2D range sum problem the range size is fixed and so we are essentially using 2D sliding window, not Kadane's.

#include <bits/stdc++.h>
using namespace std;

int main() {
  int H,W,S; scanf("%d %d %d",&H,&W,&S);
  vector<vector<int>> window(H,vector<int>(W,0));
  vector<vector<int>> A(H,vector<int>(W,0));
  
  for (int i=0;i<H;++i) {
    string s; cin >> s;
    int total = 0;
    for (int j=0;j<W;++j) {
        window[i][j] = (s[j] == '*');
        total += window[i][j];
        A[i][j] = total;
        if (i > 0)
          A[i][j] += A[i-1][j];
    }
  }

  int maxTotal = 0;
  int bestPosnI,bestPosnJ;
  for (int i=0;i<=H-S;++i) {
    for (int j=0;j<=W-S;++j) {
      int thisTotal;
      thisTotal = A[i+S-2][j+S-2] - A[i][j+S-2] - A[i+S-2][j] + A[i][j];
      if (thisTotal > maxTotal) {
        maxTotal = thisTotal;
        bestPosnI = i;
        bestPosnJ = j;
      }
      
    }
  }
  cout << maxTotal << endl;
  for (int i=0;i<H;++i) {
    for (int j=0;j<W;++j) {
      if (i == bestPosnI && j == bestPosnJ) {
        printf("+");
        for (;j<bestPosnJ+S-2;++j)
          printf("-");
        printf("+");     j++;   
      }
      else if (i == bestPosnI+S-1 && j == bestPosnJ) {
        printf("+");
        for (;j<bestPosnJ+S-2;++j)
          printf("-");   
        printf("+"); j++;
      } 
      else if (j == bestPosnJ && bestPosnI < i && i < bestPosnI+S) {
        printf("|");
      } 
      else if (j == bestPosnJ+S-1 && bestPosnI < i && i < bestPosnI+S) {
        printf("|");
      }
      else {
        printf("%c",(window[i][j] ? '*' : '.'));
      }
        
    }
    printf("\n");
  }

  
}