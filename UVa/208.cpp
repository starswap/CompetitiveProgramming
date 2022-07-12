#include <bits/stdc++.h>
using namespace std;

int V;
vector<int> path;
vector<vector<int>> AL(21);
int noPaths = 0;
//vector<vector<int>> paths;

void dfs(int u,int visited, int skip) {
//  printf("%d", u);
  if (u == V) {
 //   paths.push_back(path);
//    for (auto path : paths) {
      bool first = true;
      for (int w : path) {
        if (first)
          first = false;
        else
          printf(" "); 
        printf("%d",w);
      }
      printf("\n");
  //  }   
    noPaths++;
  } else {
    for (int v : AL[u]) {
      if (!(visited & (1<<v)) && !(skip & (1<<v))) {
        path.push_back(v);
        visited ^= (1<<v);
        int old = noPaths;
        dfs(v,visited,skip);
        if (old == noPaths) {
          skip ^= (1<<v);
        }
        visited ^= (1<<v);
        path.pop_back();
      }  
    }
  }
}


int main() {
  int caseNo = 1;
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  while (scanf("%d",&V) != EOF) {
    
    int u,v;
    path = {1};    
    AL.assign(21,vector<int>());
    noPaths = 0;

    
    while (scanf("%d %d",&u,&v), !(u == 0 && v == 0)) {
      AL[u].push_back(v);
      AL[v].push_back(u);
    }
    printf("CASE %d:\n",caseNo);
    for (vector<int> &vec : AL) {
      sort(vec.begin(),vec.end());
    }

    
    dfs(1,2,0);

    
    printf("There are %d routes from the firestation to streetcorner %d.\n",noPaths,V);
    caseNo++;
  }
  return 0;
}