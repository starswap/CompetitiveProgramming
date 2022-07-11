#include <bits/stdc++.h>

using namespace std;

int moves = 0;
vector<int> needs;

pair<int,int> dfs(int u,const vector<vector<int>> &c,const vector<int> &p,vector<int> &m) {
  int need,pushUp;
  if (c[u].size() == 0) { //leaf node.
    if (m[u] == 0) {
      need = 1;
      pushUp = 0;
    } else {
      need = 0;
      pushUp = m[u] - 1;
    }
    m[u] -= pushUp; 
  } else {
    int pushReceived = 0;
    int needsBelow = 0;
    for (int v : c[u]) {
      auto [vNeed,vPush] = dfs(v,c,p,m);
      pushReceived += vPush;
      needsBelow += vNeed; 
    }

    m[u] += pushReceived;
    if (m[u]-1-needsBelow > 0) {
      pushUp = m[u]-1-needsBelow;
      need = 0;
    } else {
      need = -(m[u]-1-needsBelow);
      pushUp = 0;
    }
  }
  moves += pushUp;
  needs[u] = need;
  return make_pair(need,pushUp);
}

//Critique: Clearly all you are doing here is summing the values in needs. Therefore you can just do that in the first traversal so an improved algorithm could solve the problem with just one traversal
void calculateMoves(int u,const vector<vector<int>> &c,const vector<int> &p,vector<int> &m) {
  for (int v : c[u]) {
    moves += needs[v];
    m[v] += needs[v]; //don't really need to actually transfer it
    m[u] -= needs[v];
    calculateMoves(v,c,p,m);
  }
} 

int main() {
  int n;
  while(scanf("%d",&n), n != 0) {
    vector<int> p(n,-1);
    vector<vector<int>> c(n);
    vector<int> m(n,-1);
    needs.resize(n);
    fill(needs.begin(),needs.end(),0);
    moves = 0;    
    for (int i=0;i<n;++i) {
      int v,numChildren;
      scanf("%d %d %d",&v,&m[i],&numChildren);
      for (int j=0;j<numChildren;++j) {
        int child; cin >> child; child--;
        p[child] = i;
        c[i].push_back(child);
      }
    }

    int root;
    for (int j=0;j<n;++j) {
      if (p[j] == -1)
        root = j;
    }

    dfs(root,c,p,m);
    calculateMoves(root,c,p,m);

    cout << moves << endl;
  }  
}