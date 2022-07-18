#include <bits/stdc++.h>
using namespace std;
int main() {
  int N,M; scanf("%d %d",&N,&M);
  vector<vector<int>> A(N,vector<int>(M,0)); //partial sums to (0,0)
  vector<vector<int>> G(N,vector<int>(M,0)); //campsite grid
  for (int n=0;n<N;++n) {
    string s;
    cin >> s;
    int rowTotal = 0;
    for (int m=0;m<M;++m) {
      G[n][m] = (s[m] == '#');
      rowTotal += G[n][m];
      if (n >= 1)
        A[n][m] = A[n-1][m]+rowTotal;
      else
        A[n][m] = rowTotal;
    }
  }

  vector<vector<int>> TLC(N,vector<int>(M,0)); 
  for (int n=0;n<N;++n) { //for each top left corner
    for (int m=0;m<M;++m) {
      if (G[n][m] == 1) {TLC[n][m] = 0;continue;}
      int lo = 1;
      int hi = min(N-n,M-m);
      while (lo != hi) { //BSTA the largest tent we can place with this one as the Top left corner.
     //   cout << lo << "," << hi << endl;
        int sideLength = ceil(static_cast<double>(lo+hi)/2.0);
        int TLCn = n;
        int TLCm = m;
        int BRCn = n+sideLength-1;
        int BRCm = m+sideLength-1;
        int sumTotal;
        if (TLCn == 0) {
          if (TLCm == 0) {
            sumTotal = A[BRCn][BRCm];
          }
          else {
            sumTotal = A[BRCn][BRCm] - A[BRCn][TLCm-1];
          }
        } else if (TLCm == 0) {
          sumTotal = A[BRCn][BRCm] - A[TLCn-1][BRCm];
        } else {
          sumTotal = A[BRCn][BRCm] - A[TLCn-1][BRCm] - A[BRCn][TLCm-1] + A[TLCn-1][TLCm-1];
        }
        if (sumTotal == 0) // Can do it as there are no #s in this region
          lo = sideLength;
        else
          hi = sideLength - 1;  
      }
      TLC[n][m] = hi; //=lo=sideLength;
    }
  }

  vector<vector<int>> LPropped(N,vector<int>(M,0));
  for (int n=0;n<N;++n) { //for each top left corner
    priority_queue<pair<int,int>> pq;
    for (int m=0;m<M;++m) {
      pq.emplace(TLC[n][m],m+TLC[n][m]-1);
      int top,expiry;
      top = get<0>(pq.top());
      expiry = get<1>(pq.top());
      while (expiry < m) { //largest tent we can propagate LtoR.
        if (top == 0 && expiry == m-1)
          break;        
        pq.pop();//grrr no structured bindings ;(
        top = get<0>(pq.top());
        expiry = get<1>(pq.top());
      }
      LPropped[n][m] = top;
    }
  }
  
  vector<vector<int>> UPropped(N,vector<int>(M,0));
  for (int m=0;m<M;++m) { //for each top left corner
    priority_queue<pair<int,int>> pq;
    for (int n=0;n<N;++n) {
      pq.emplace(LPropped[n][m],n+LPropped[n][m]-1);
      int top,expiry;
      top = get<0>(pq.top());
      expiry = get<1>(pq.top());
      while (expiry < n) { //largest tent we can propagate LtoR.
        pq.pop();//grrr no structured bindings ;(
        if (top == 0 && expiry == n-1)
          break;        
        top = get<0>(pq.top());
        expiry = get<1>(pq.top());
        
      }
      UPropped[n][m] = top;
    }
  }  

  int Q; scanf("%d",&Q);
  for (int q=0;q<Q;++q) {
    int r,c;
    scanf("%d %d",&r,&c);
    printf("%d\n",(UPropped[r-1][c-1])*(UPropped[r-1][c-1]));
  } 
   return 0; 
}