#include <bits/stdc++.h>
using namespace std;
int main() {
  int x,y;
  int N=-1;
  int R=-1;
  int caseNo = 1;
  while (scanf("%d %d",&N,&R), !(N == 0 && R == 0)) {
    vector<tuple<double,double,double>> islands;
    bool impossible = false;
    for (int n=0;n<N;++n) {
      cin >> x; cin >> y; 

      double stationX = sqrt(pow(R,2)-pow(y,2)) + x; // furthest right point on x axis that will cover it. 

      islands.emplace_back(stationX,x,y);
      if (y > R)
        impossible = true;
    }
  
    if (impossible) {
      printf("Case %d: -1\n",caseNo);
    }
    else {
      sort(islands.begin(),islands.end());
    
      int i = 0;
      int stations = 0;
      double stationX = -1e9;
      while (i < N) { 
        auto &[sx,x,y] = islands[i];
        
        if (hypot(stationX-x,y) <= R) ++i; //skip as covered already
        else {
          stationX = sx;
          stations++; ++i;
        }   
      }
      printf("Case %d: %d\n",caseNo,stations); 
    }
    caseNo++;
  }
}