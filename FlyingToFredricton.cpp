#include <bits/stdc++.h>
using namespace std;
int main() {
  int S;
  cin >> S;
  for (int s=0;s<S;s++) {
    int N;cin >> N;
    unordered_map<string,int> places;
    for (int n=0;n<N;n++) {
      string name;
      cin >> name;
      places[name] = n;
    }
    int M; cin >> M;
    vector<vector<pair<int,int>>> AL(N,vector<pair<int,int>>());
    vector<vector<int>> AM(N,vector<int>(N,1e9));
    for (int m=0;m<M;m++) {
      string p1;string p2;int cost;
      cin >> p1;cin >> p2; cin >> cost;
      AM[places[p1]][places[p2]] = min(AM[places[p1]][places[p2]],cost);
    }
    for (int u=0;u<N;u++) {
      for (int v=0;v<N;v++) {
        AL[u].push_back(make_pair(v,AM[u][v]));
      }
    }
    
    vector<vector<int>> dist(N,vector<int>(N+2,1e9)); //to x with y stopovers.
    dist[0][0] = 0;
    for (int i=0;i<N-1;i++) {
      for (int u=0;u<N;u++) {
        for (int stop=0;stop<N;stop++) {
          if (dist[u][stop] != 1e9) {
            for (auto &[v,w] : AL[u]) {
              dist[v][stop+1] = min(dist[v][stop+1],dist[u][stop]+w);
            }
          }
        }
      }
    }

    int Q;
    cin >> Q;
    cout << "Scenario #" << s+1 << '\n';
    for (int q=0;q<Q;q++) {
      int stopovers;
      cin >> stopovers;
      int result = 1e9;
      for (int st=0;st<=min(stopovers+1,N+1);st++) {
        result = min(result,dist[N-1][st]);
      }
      if (result == 1e9)
        cout << "No satisfactory flights";
      else
        cout << "Total cost of flight(s) is $" << result;
      cout << '\n';
    }
    if (s != S-1)
      cout << '\n';
  } 
  return 0;
}
