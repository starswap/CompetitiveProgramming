//Requires:
  // C++ 17 (decomposition declaration)
  // Large stack size (input up to 800000 vertices so prepBinLift can overflow); 16 MiB was enough for me. (set with ulimit -s 16777216 on Linux; Windows compile with g++ Facebook/2021/Round2/B.cpp -Wl --stack,16777216)

#include <bits/stdc++.h>
using namespace std;

inline int LSOne(int a){
  return a&-a;
}

vector<vector<int>> AL; //Adjacency list for tree
vector<int> F; //Frequency of node n is F[n].

int logn; //log(N)
int dp[800001][23]; //dp[u][2^n] 20 is minimum; give a bit of extra space; for binary lifting
int level[800001]; //number of nodes on shortest path from node n to the root i.e. depth. 0 is the root.
int LCA[800001]; //LCA[f] is the LCA of all nodes at frequency f

pair<int,int> dfs(int u,int p) {
  //O(N); No need to check for already visited as it's a tree; we check for parent. 
  //Solves the problem by the principle that we will cut an edge joining subtree s to parent p if and only if subtree s contains all elements in the tree at frequencies f1, f2, f3 etc where f1, f2, f3 are the frequencies found in subtree S. 
  // Return pair of (highest/lowest node you need to go to such that the subtree rooted at that node contains all elements with frequencies present in the /current/ subtree, number of cut edges in this subtree)
  
  int maxNeedToGoTo = LCA[F[u]]; //For nodes in this subtree, what is the highest (lowest!) node we need to go to in order to have all nodes of all frequencies which are present; i.e. in order to be able to chop the subtree from the parent. Initially, we only need to go as far as the LCA of all nodes at frequency f where f is the frequency of this node. 
  int cutEdgesTotal = 0; //So far no edges have been cut.
  for (int v : AL[u]) {
    if (v != p) { //don't revisit
      auto [subNeedTo,cutEdges] = dfs(v,u); //recurse first to reach root, then build up.
      cutEdgesTotal += cutEdges; //no of cut edges in this  
      if (level[subNeedTo] < level[maxNeedToGoTo]) //Subtree rooted at v requires us to go higher up (as root is level 0) in the hierarchy to gain a set containing all nodes of the frequencies in the subtree rooted at v. As this subtree contains subtree rooted at v we need to go at least this high.
        maxNeedToGoTo = subNeedTo;
    }
  }
  if (maxNeedToGoTo == u) //can cut edge between this subtree and its parent since this subtree contains every node of the frequencies present.
    cutEdgesTotal += 1;

  //Note that the root will think it can cut the edge to its parent if you use a value of -1 as the parent, so subtract 1 from the return value.
  return make_pair(maxNeedToGoTo,cutEdgesTotal);
}


void prepBinLift(int u, int l) {
  //Binary lifting preprocessing
  //  O(NlogN);
  
  level[u] = l; // save depth for later
  
  int i = 0; 
  while (dp[u][i] != -1) { //O(logN) since we iterate over possible 2^ns. While we can jump this high.
    dp[u][i+1] = dp[dp[u][i]][i]; //propagate jumps (dp recurrence)
    i++;
  }
  
  for (int v : AL[u]) {
    if (v != dp[u][0]) { // not parent
      dp[v][0] = u; //save parent
      prepBinLift(v,l+1); 
    }
  }
  
}

int binLiftLCA(int u, int v) {
  //O(log N)
  
  if (level[u] < level[v]) //Ensure u is deeper in the tree than v.
    swap(u,v);
  
  int diff = level[u]-level[v]; //difference in depths
  
  //Make same level
  while (diff > 0) { //O(log n)for each 1 bit in the difference in depths - binary representation
    int twoPowV = LSOne(diff);
    u = dp[u][__builtin_ctz(twoPowV)]; //shift u up by this one
    diff ^= twoPowV;
  }
  
  //Now u and v have the same depth

  if (u == v) //one was child of other and so they are now the same.
    return u;
  
  for (int i=logn;i>=0;i--) { //O(log n)
    if (dp[u][i] != dp[v][i]) { //shift up as long as they don't become the same by shifting up. (note this deals with possibly shifting off the top of the tree fine as they would both be the same, -1, if this occurs)
      u = dp[u][i];
      v = dp[v][i];
    }
  }
  
  //u's parent = v's parent = LCA.
  return dp[u][0];
}


int main() {
  int T; scanf("%d",&T);
  
  for (int t=1;t<=T;++t) {
    int N; scanf("%d",&N);

    F.assign(N,0);
    AL.assign(N,vector<int>());
    
    for (int n=0;n<N-1;++n) {
      int A, B;  //as in problem description
      scanf("%d %d",&A,&B); A--; B--; //ensure vertex numbering starts at 0.
      AL[A].push_back(B);
      AL[B].push_back(A);      
    }
    
    for (int n=0;n<N;++n) { //Get frequencies
      scanf("%d",&F[n]);
    }

    //Reset after each TC.
    memset(dp,-1,sizeof dp);
    memset(LCA,-1,sizeof LCA);

    //Max number of shifts upwards in binary lifting is 2^logn. (we add 1 just to make sure we have enough) 
    logn = ceil(static_cast<double>(log(N))/static_cast<double>(log(2)))+1;
    prepBinLift(0,0); //start at vertex 0, depth of 0.

    //For each possible frequency get the LCA, highest node needed to make sure we have every one of that freq in the subtree
    for (int n=0;n<N;++n) {
      if (LCA[F[n]] == -1)
        LCA[F[n]] = n; //not seen this frequency before; as long as we have this node we have all of them
      else
        LCA[F[n]] = binLiftLCA(LCA[F[n]],n); // 2nd+ node of this frequency; need to use LCA
    }
  
    printf("Case #%d: %d\n",t,dfs(0,-1).second-1); //subtract one for the cut edge from the root to its pseudo parent which we introduced to make the answer easier to extract.
  }
  return 0;
}
