#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
vector<int> postOrder;
void dfs(vector<vector<int>>&AL,int u) {
  visited[u] = true;
  for (int v : AL[u]) {
    if (!visited[v]) 
      dfs(AL,v);
  }
  postOrder.push_back(u);
}

template <typename T>
ostream& operator << (ostream& o, vector<T> v) {
  o << "[";
  for (auto a : v) {
    o << a << ",";
  }
  o << "]";
  return o;
}

int Kosaraju(vector<vector<int>>&AL,vector<vector<int>> &AL_T) {
  int n = AL.size();
  visited.assign(n,false);
  postOrder.clear();

  for (int i=0;i<n;i++) {
    if (!visited[i]) {
      dfs(AL,i);
    }
  }
  visited.assign(n,false);
  int SCCs = 0;
  for (int i=n-1;i>=0;i--) {
    if (!visited[postOrder[i]]) {
      dfs(AL_T,postOrder[i]);
      SCCs++;
    }
  }
  return SCCs;
}

int main() {
  int P,T;
  cin >> P;
  cin >> T;
  while (P != 0 || T != 0) {
    string rest;
    getline(cin,rest);
    unordered_map<string,int> People;
    for (int i=0;i<P;i++) {
      string person;
      getline(cin,person);
      People.insert(make_pair(person,i));
    }

    vector<vector<int>> AL(P,vector<int>());
    vector<vector<int>> AL_T(P,vector<int>());

    for (int t=0;t<T;t++) {
      string p1;
      string p2;
      getline(cin,p1);
      getline(cin,p2);
      AL[People[p1]].push_back(People[p2]);
      AL_T[People[p2]].push_back(People[p1]);
    }

    cout << Kosaraju(AL,AL_T) << '\n';

    cin >> P;
    cin >> T;
  }

  return 0;
}
