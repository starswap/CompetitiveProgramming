#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

int main() {
  int N;
  while (scanf("%d",&N), N != 0) {
    vector<double> radii(N);
    for (int n=0;n<N;++n) {
      cin >> radii[n];
    }
    sort(radii.begin(),radii.end());

    double total = 0;
    bool yes = false;
    for (int i=0;i<N-1;++i) {
      total += radii[i];
      if (total > radii[i+1]-EPS)
        yes = true;
    }
    cout << ((yes) ? "YES" : "NO") << endl;
    
    
  }
}