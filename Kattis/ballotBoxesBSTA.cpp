#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,B;
  while (scanf("%d %d",&N,&B),!(N==-1&&B==-1)) {
    vector<int> popns(N);
    for (int n=0;n<N;++n) {
      cin >> popns[n];
    }

    int lo = 1;
    int hi = 5000001;
    while (!(hi == lo)) {
      int numBoxes = 0;
      int m = (hi+lo)/2;
      for (int p : popns)
        numBoxes += ceil(static_cast<double>(p)/static_cast<double>(m));

      if (numBoxes <= B)  //can do it with this or less
        hi = m;
      else //can't do it with this or less
        lo = m+1;
    }
    cout << lo << endl;
  }
}