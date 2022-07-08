#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,B;
  while (scanf("%d %d",&N,&B), !(N == -1 && B == -1)) {
    priority_queue<pair<double,double>> pq; //(no per box, no boxes)
    for (int i=0;i<N;++i) {
      double a; cin >> a;
      pq.emplace(a,1.0);
    }
    B -= N;
    while (B > 0) {
      auto [perBox,boxes] = pq.top(); pq.pop();
      double total = perBox*boxes;
      pq.emplace(total/(boxes+1),boxes+1);
      B--;
    }
    auto [perBox,boxes] = pq.top();
    cout << ceil(perBox) << endl;    
  }
  return 0;
}