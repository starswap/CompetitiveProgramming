//The solution 208.cpp, recursive backtracking with some pruning is fast enough to get AC and not TLE on the test cases used by the judge. However, this input is clearly not exhaustive because the complete graph in 208HarderInput.txt meets the constraints set out in the problem and yet we would get TLE on this input.
//Due to input/output constraints, it is infeasible to output all paths from source to sink on this graph, but we can count them instead using DP. A basic analysis (2^20 possible visited sets * 20 nodes at which we are located = ~~ 20M) shows that this will be quick enough.
//Indeed it is quick enough, and running this code on that input gives the correct answer of: 17403456103284421 which can be calculated from 1+18+18*17+18*17*16+18*17*16*15+....+18!

#include <bits/stdc++.h>
using namespace std;

int V;
vector<vector<int>> AL(21);
//vector<vector<int>> paths;
static long long memo[2097151][20]; //2^21-1 = 2097151.

int countExec = 0;
long long dfs(int u,int visited,long long memo[2097151][20]) {
  long long pathsToEnd = 0;
  countExec++;
  if (u != V) {
    for (int v : AL[u]) {
      if (!(visited & (1<<v))) {
        visited ^= (1<<v);
        if (memo[visited][v] != -1)
          pathsToEnd += memo[visited][v];
        else 
          pathsToEnd += dfs(v,visited,memo);
        visited ^= (1<<v);
      }
    }
  } else {
    pathsToEnd = 1;
  }
  memo[visited][u] = pathsToEnd;
  return pathsToEnd;
}


int main() {
  int caseNo = 1;
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  while (scanf("%d",&V) != EOF) {
    V--;
    
    int u,v;
    AL.assign(20,vector<int>());

    
    while (scanf("%d %d",&u,&v), !(u == 0 && v == 0)) {
      v--;u--;
      AL[u].push_back(v);
      AL[v].push_back(u);
    }
    printf("CASE %d:\n",caseNo);
    for (vector<int> &vec : AL) {
      sort(vec.begin(),vec.end());
    }

    for (int i=0;i<2097151;++i) {
      for (int j=0;j<20;++j) {
        memo[i][j] = -1;
      }
    }
    printf("There are %lld routes from the firestation to streetcorner %d.\n",dfs(0,1,memo),V+1);
    printf("%d",countExec);
    caseNo++;
  }
  return 0;
}