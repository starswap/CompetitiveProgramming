#include <bits/stdc++.h>
using namespace std;

void DFS(vector<vector<int>> &AL,vector<bool>&visited,int v) {
  if (visited[v])
    return;
  else {
    visited[v] = true;
    for (int u : AL[v])
      DFS(AL,visited,u);
  }
}

bool eulerCheck(vector<vector<int>> &AL) {
  //check if an euler tour is possible on undirected graph
  
  //check for even degree
  for (vector<int> v : AL) {
    if (div(v.size(),2).rem == 1)
      return false;
  }

  //check for connected, starting from a vertex with at least one edge.
  vector<bool> visited(AL.size(),false);
  int start;
  for (start=0;AL[start].size()==0;start++) {};
  DFS(AL,visited,start);
  for (int i=0;i<visited.size();i++) {
    if (visited[i] == false && AL[i].size() != 0) //we were unable to reach the vertex and it has an edge attached to it. Therefore the graph is disconnected. If it has no edge attached, while the graph is still not connected to it, this doesn't affect the Euler tour property.
     return false;
  }
  return true;
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int V,E;
  while (cin >> V) {
    cin >> E;
    if (E == 0){
      cout << "Not Possible" << '\n'; //corner case - no roads.
      continue;
    } 
    vector<vector<int>> AL(V,vector<int>(0));
    for (int e=0;e<E;e++) {
      int u,v;
      cin >> u;
      cin >> v;
      AL[v].push_back(u);
      AL[u].push_back(v);
    }
    bool res = eulerCheck(AL);
    if (res)
      cout << "Possible" << '\n';
    else
      cout << "Not Possible" << '\n';
  } 
}
