//Principle:
  // There are only 18 (not 20) hotels and so we can use O(2^n n^2) TSP subroutine on these
  // There are 18C9 possible first half sets of hotels (which is not many, only 49K)
  // Can we iterate over all of these?
  // The journey can be split into 2 sections, each of which is divided in half:
    //1. HQ -> Attraction; 1st half of hotels
    //2. HQ -> Attraction; 2nd half of hotels
    //3. Attraction -> HQ; 1st half of hotels
    //4. Attraction -> HQ; 2nd half of hotels
  //After much deliberation, one realises that:
    // If we compute the min cost Hamiltonian-Path from start to end via every vertex, and end to start via every vertex, using DP, 2 and 4 are already computed as they are a subproblem of this H-Path problem when only half of the hotels remain to be visited
    // 1 and 3 can be viewed the opposite way as, rather than "min cost path from Start to halfway using only certain nodes" "min cost path from halfway to end (where end is start) with only certain nodes left", and these are also computed in the original TSP.
  //Therefore we can pre-compute using the H-Path/TSP code all of the states in 2 * 2^18*18^2 = 170M
  //... and then for each possible interface between these parts 1-4 (for each first half subset and final node in that subset), put the results together to get a total cost, and then minimise this overall.  

#include <bits/stdc++.h>
using namespace std;

const int INF = 100000000;

inline int LSOne(int v) { //Lease significant one bit; Two's Complement
  return (v&-v);
}

vector<vector<int>> costs(20,vector<int>(20,INF));

int dp1[262144][20]; //dp1[bitmask][u]; stores results for 
int dp2[262144][20]; //dp2[bitmask][u], up to 18 and 2^18; stores results for "on the way back - Attraction to HQ"

int tsp(int remainingBM, int u, int target, int dp[262144][20]) {
  //Hamiltonian Path for fully connected graph - goes from start to "target"
    //remainingBM = bitmask where each bit is a node in the graph; 1 is unvisited and 0 is visited
    //u = current vertex 
    //target = final vertex in the path; not included in the bitmask (only hotels in bitmask)
    //dp = either dp1 on the way there or dp2 on the way back
  
  if (remainingBM == 0) //all visited so end the path by jumping to target
    dp[remainingBM][u] = costs[u][target];
  
  if (dp[remainingBM][u] != -1) //Already computed in DP
    return dp[remainingBM][u]; //return cached value
  
  int prevRemaining = remainingBM; //save a copy so we can mutate remainingBM but pass the old version recursively
  int best = INF; 
  while (remainingBM > 0) { //Iterate over all unvisited nodes
    int twoPowV = LSOne(remainingBM); //lowest untried vertex
    int v = __builtin_ctz(twoPowV)+1; //(acts as a logarithm to find out which bit is set); add 1 since node 0 is HQ which is not in the bitmask to save space and time.
    best = min(best, costs[u][v] + tsp(prevRemaining ^ twoPowV,v,target,dp)); //minimum cost for moving next to vertex v, over all v.
    remainingBM ^= twoPowV; //erase this vertex from the bitmask so that we take the next vertex on the next iteration.
  }
  dp[prevRemaining][u] = best; //cache and return
  return best;
}

int n, m; // n = number of buildings (hotels + attraction + HQ) i.e. nodes ; m = number of edges
int nHotels; // = n-2

inline int safeNot(int v) {
  //Takes the bitwise not of a bitmask of length nHotels
  //nHotels < 32 so plain ~ will give a load of 1s at the beginning of the mask
  //... in the region for the unused bits
  //We set these back to 0 to avoid thinking we need to visit those nodes.
  return ~v & ((1<<nHotels)-1);
}

int recursiveSolve(int BM, int numSet,int current) {
  //After having done TSP in both directions,
  //Try all possible subsets (nHotels C floor(nHotels/2)) to be the first half that are visited first from both directions.
    // (this routine is actually closer to 2^18 because we only give up once we get to the end of the array and there are not enough elements in the subset. This is still AC because 2^18 is only 262K but we could prune earlier by checking if numSet+nHotels-current >= nHotels/2 or similar i.e. is there at least half remaining?)
  //We generate these subsets recursively
  //BM is the bitmask where the on bits represent the set in the first half.

  //Done generating so compute cost of this subset
  if (numSet >= nHotels/2 && numSet != 0) { 
    // (when nHotels = 1 we have a special case where we don't care if the hotel is in the first or second half, so to ensure we count it we force it into the first half).
    int best = INF;
    //For a given first half set, we might finish that first half set on any of the nodes in the set
    //The node we finish the first half on in the "way there" (i.e. S->E) (=u) could be different to the node we finish in (E->S) (= v).
    //.. so we try all of those, for a max of 18C9*9*9 = 4M ops.
    for (int u=1;u<=nHotels;++u) {
      for (int v=1;v<=nHotels;++v) {
        if ((BM & (1<<(u-1))) && (BM & (1<<(v-1)))) {//Skip if either final vertex in BM is not actually in BM (easier to iterate this way than to iterate over the on bits) 

          //Compute score for this segregation:
          //From first to last:
            //S->E: 1st half (computed by noting that this is equal to the E->S cost with that subset left)
            //S->E: 2nd half (everything except the first half remains)
            //E->S: 1st half (again computed in reverse)
            //E->S: 2nd half 
          int newScore = tsp(BM^(1<<(u-1)),u,0,dp2) + tsp(safeNot(BM),u,n-1,dp1) + tsp(BM^(1<<(v-1)),v,n-1,dp1) + tsp(safeNot(BM),v,0,dp2);

          best = min(best,newScore); //We want minimum cost option
        }
      }
    }
    return best;
  }
    //Continue subset generation
  else if (current > nHotels) //We didn't pick enough (for half) in this subset - stop 
    return INF;
  else {
    return min(
      recursiveSolve(BM | (1<<(current-1)),numSet+1,current+1), //Take this one and set bit
      recursiveSolve(BM,numSet,current+1) //Don't take this one
    );
  }
  
}




int main() {
  int caseNo = 1; 
  while (scanf("%d %d",&n,&m) != EOF) {
    costs.assign(n,vector<int>(n,INF)); //Adjacency matrix; Needed for Floyd Warshall.
    
    for (int i=0;i<m;++i) {
      int u,v,c;
      scanf("%d %d %d",&u,&v,&c);
      costs[u][v] = c;
      costs[v][u] = c;
    }

    //TSP subroutine needs fully connected graph; compute APSP costs via FloydWarshall to achieve this.
    // (i.e. cost from any hotel to any other, passing through some without visiting if necessary)
    for (int k=0;k<n;++k)
      for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
          costs[i][j] = min(costs[i][j],costs[i][k]+costs[k][j]);
    
    nHotels = n-2; //Separate variable used for documentation

    //Blank out DPs before each test case so we know what we have computed
    memset(dp1,-1,sizeof dp1);
    memset(dp2,-1,sizeof dp2);

    //Populate DPs (TBH you could skip this and do it only when you need it in recursiveSolve, but originally this is how I thought of it)
    tsp((1<<nHotels)-1,0,n-1,dp1);
    tsp((1<<nHotels)-1,n-1,0,dp2);

    //Get answer and output
    int ans = recursiveSolve(0,0,1);
    
    printf("Case %d: %d\n",caseNo,ans);
    ++caseNo;
  }
  return 0;
}