#include <bits/stdc++.h>
using namespace std;

class UFDS {
  private:
    vector<int> p;
    vector<int> rank;
    int n;

  public:
    UFDS(int a):n(a) {
      for (int i=0;i<n;i++) {
        p.push_back(i);
      }
      rank.assign(n,1);
    }

    int findSet(int a) {
      if (p[a] == a) 
        return a;
      else {
        int x = findSet(p[a]);
        p[a] = x;
        return x;
      }
    }

    void unionSet(int a,int b) {
      int x = findSet(a);
      int y = findSet(b);

      if (x==y) {return;}

      if (rank[x] > rank[y]) {
        p[y] = x;
      } else if (rank[y] > rank[x]){
        p[x] = y;
      }
      else {
        p[x] = y;
        ++rank[y];
      }
    }

    bool isSameSet(int a,int b) {
      return findSet(a) == findSet(b);
    }

};


vector<int> dfs_num;
vector<int> dfs_low;
vector<int> dfs_parents;
int dfsCounter;
void findBridges(const vector<vector<int>>& AL, int u,UFDS &bridgesOnly) {
  dfs_num[u] = dfs_low[u] = dfsCounter;
  dfsCounter++;
  
  for (int v : AL[u]) {
    if (dfs_num[v] == -1) {
      dfs_parents[v] = u;
      findBridges(AL,v,bridgesOnly);
      if (dfs_low[v] > dfs_num[u]) {
        bridgesOnly.unionSet(u,v);
      }
      dfs_low[u] = min(dfs_low[u],dfs_low[v]);
    }
    else if (dfs_parents[u] != v) {
      dfs_low[u] = min(dfs_low[u],dfs_num[v]);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int R,C,Q; cin >> R; cin >> C; cin >> Q;
  while (R!=0 && C!=0 && Q!=0) {
    vector<vector<int>> AL(R,vector<int>(0));
    for (int c=0;c<C;c++) {
      int a,b;
      cin >> a;--a;
      cin >> b;--b;
      AL[a].push_back(b);
      AL[b].push_back(a);
    }

    UFDS bridgesOnly(R);
    dfs_num.assign(R,-1);
    dfs_parents.assign(R,-1);
    dfs_low.assign(R,INT_MAX);
    dfsCounter = 0;

    for (int s=0;s<R;s++) { //all CCs
      if (dfs_num[s] == -1)
        findBridges(AL,s,bridgesOnly);
    }

    for (int q=0;q<Q;q++) {
      int S,T; cin >> S; cin >> T; S--;T--;
      unordered_set<int> visited;
      if (bridgesOnly.isSameSet(S,T))
        cout << "Y" << '\n';
      else
        cout << "N" << '\n';
    }
    cout << "-" << '\n';

    cin >> R;
    cin >> C;
    cin >> Q;
  }

}
