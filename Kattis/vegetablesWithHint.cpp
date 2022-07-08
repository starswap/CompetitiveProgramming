#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-4;
int main() {
  double T; int N;
  scanf("%lf %d",&T,&N);

  multiset<pair<double,int>> veggies;
  for (int n=0;n<N;++n) {
    int w;
    cin >> w;
    veggies.emplace(w,0); // weight of a piece; cuts.
  }

  int cutsTotal = 0;
  while ( T <= (veggies.begin())->first/(prev(veggies.end())->first) <= T+EPS) {
    auto [pieceWeight,cuts] = *prev(veggies.end());
    double total = pieceWeight*(cuts+1);
    veggies.erase(prev(veggies.end()));
    veggies.emplace(total/(cuts+2),cuts+1);
    cutsTotal++;
  }
  cout << cutsTotal << endl;
  
  
}