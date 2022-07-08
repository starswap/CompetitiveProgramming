#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
vector<int> postOrder;
void dfs(vector<vector<int>> &AL,int u) {
  visited[u] = true;
  for (int v : AL[u]) {
    if (!visited[v]) {
      dfs(AL,v);
    }
  }
  postOrder.push_back(u);
}

void dfs2(vector<vector<int>> &AL,int u) {
  visited[u] = true;
  for (int v : AL[u]) 
    if (!visited[v])
      dfs2(AL,v);
}

int Kosaraju(vector<vector<int>> &AL,vector<vector<int>> &AL_T) {
  int n = AL.size();
  visited.assign(n,false);
  postOrder.clear();

  for (int i=0;i<n;i++) {
    if (!visited[i])
      dfs(AL,i);
  }

  visited.assign(n,false);
  vector<int> SCCs;
  for (int i=n-1;i>=0;i--) {
    if (!visited[postOrder[i]]) {
      SCCs.push_back(postOrder[i]);
      dfs(AL_T,postOrder[i]);
    }
  }

  int dominos = 0;
  visited.assign(n,false);
  for (int i=0;i<SCCs.size();i++) {
    if (!visited[SCCs[i]]) {
      dfs2(AL,SCCs[i]);
      dominos++;
    }
  }
  return dominos;
}

int main() {
  int T;
  cin >> T;
  for (int t=0;t<T;t++) {
    int N; cin >> N;
    int M; cin >> M;
    vector<vector<int>> AL(N,vector<int>());
    vector<vector<int>> AL_T(N,vector<int>());

    for (int m=0;m<M;m++) {
      int a,b;cin >> a;cin >> b;--a;--b;
      AL[a].push_back(b);
      AL_T[b].push_back(a);
    }
    cout << Kosaraju(AL,AL_T) << '\n';
  }

  return 0;
}
