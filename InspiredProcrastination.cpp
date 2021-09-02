#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,M;
  cin >> N;
  cin >> M;
  while (!(N==0&&M==0)) {
    vector<vector<pair<int,int>>> AL(N,vector<pair<int,int>>());
    for (int m=0;m<M;m++) {
      int u,v,w; cin >> u;cin>>v;cin>>w; --u;--v;
      AL[u].push_back(make_pair(v,-w));
    }

    vector<int> dist(N,1e9);
    dist[0] = 0;
    for (int n=0;n<N-1;n++)  {
      bool changed = false;
      for (int u=0;u<N;u++) {
        if (dist[u] != 1e9) {
          for (auto &[v,w] : AL[u]) {
            if (dist[v]>dist[u]+w) {
              dist[v] = dist[u]+w;
              changed = true;
            }
          }
        }
      }
      if (changed == false)
        break; 
    }
    bool hasNegCycle = false;
    for (int u=0;u<N;u++) {
      if (dist[u] != 1e9) {
        for (auto &[v,w] : AL[u]) {
          if (dist[v]>dist[u]+w) {
            hasNegCycle = true;
            break;
          }
        }
      }
      if (hasNegCycle) {
        break;
      }
    }
  
    if (hasNegCycle) {
      cout << "Unlimited!" << '\n';
    } else {
      int mini = 1e9;
      for (int c : dist) {
        mini = min(mini,c);
      }
      cout << -mini << '\n';
    }
    cin >> N;
    cin >> M;
  }

  return 0;
}
