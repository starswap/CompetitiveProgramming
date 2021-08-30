#include <bits/stdc++.h>
using namespace std;

int vertexCounter = 0;
int dfs_root = 0;
int rootChildren = 0;
vector<int> dfs_num;
vector<int> dfs_low;
vector<int> dfs_parent;
vector<int> artPoints;
void findArticulationPoints(vector<vector<int>>& AL,int u) {
  dfs_num[u] = vertexCounter;++vertexCounter;
  dfs_low[u] = dfs_num[u];

  for (int v : AL[u]) {
    if (dfs_num[v] == -1) {
      dfs_parent[v] = u;
      if (u == dfs_root) {rootChildren++;} 
      findArticulationPoints(AL,v);
      if (dfs_low[v] >= dfs_num[u]){      
        artPoints[u] = 1;
      }
      
      dfs_low[u] = min(dfs_low[u],dfs_low[v]);
    } else if (v != dfs_parent[u]){
      dfs_low[u] = min(dfs_low[u],dfs_num[v]);
    }
  }
}


int main() {
  int N;
  cin >> N;
  while (N != 0) {
    vector<vector<int>> AL(N,vector<int>(0));
    int S;
    cin >> S;
    while (S != 0) {
      string rest;
      getline(cin,rest);
      istringstream iss(rest);
      int T;
      while (iss >> T) {
        AL[S-1].push_back(T-1);
        AL[T-1].push_back(S-1);
      }
      cin >> S;
    }
    
    vertexCounter = 0;
    dfs_root = 0;
    rootChildren = 0;
    dfs_num.assign(N,-1);
    dfs_low.assign(N,INT_MAX);
    dfs_parent.assign(N,-1);
    artPoints.assign(N,0);

    findArticulationPoints(AL,0);
    artPoints[dfs_root] = (rootChildren > 1);

    int articulationPoints = 0;
    for (int art : artPoints) {
      articulationPoints += art;
    }

    cout << articulationPoints << endl;

    cin >> N;
  }
  return 0;
}
