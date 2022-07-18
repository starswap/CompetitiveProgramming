#include <bits/stdc++.h>
using namespace std;

int main() {
  int H,W,S; scanf("%d %d %d",&H,&W,&S);
  vector<vector<int>> window(H,vector<int>(W,0));
  for (int i=0;i<H;++i) {
    string s; cin >> s;
    for (int j=0;j<W;++j) {
        window[i][j] = (s[j] == '*'); 
    }    
  }

  int maxTotal = 0;
  int bestPosnI,bestPosnJ;
  for (int i=0;i<=H-S;++i) {
    for (int j=0;j<=W-S;++j) {
      int thisTotal = 0;
      for (int k=1;k<S-1;k++) {
        for (int l=1;l<S-1;l++) {
          thisTotal += window[i+k][j+l];
        }
      }

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