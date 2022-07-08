#include <bits/stdc++.h>
using namespace std;

int LN; //should really be log of depth but log of num nodes will pass here. 

void calcPagesFromRoot(int u, vector<int> &pagesFromRoot, const vector<int> &pages,vector<bool> &visited,vector<vector<int>> &AL,int page,vector<int> &CC) {
    visited[u] = true;
    pagesFromRoot[u] = page+pages[u];
    bool hasChild = false;
    for (int v : AL[u]) {
        calcPagesFromRoot(v,pagesFromRoot,pages,visited,AL,page+pages[u],CC);
        hasChild = true;
    }
    if (!hasChild)
        CC.push_back(u);
}

void preprocessBinLift(int u,vector<int> &lvl,vector<vector<int>> &dp,vector<vector<int>> &AL,vector<int> &visited, int cc) {
    visited[u] = cc; //stores which conc it is in.
    
    for (int i=1;i<LN;++i) {
        if (dp[u][i-1] != -1) //if it is -1 then you can't jump that far
            dp[u][i] = dp[dp[u][i-1]][i-1];
    }
    
    for (int v : AL[u]) {
        dp[v][0] = u; //***
        lvl[v] = lvl[u] + 1;
        preprocessBinLift(v,lvl,dp,AL,visited,cc);
    }
    
}

int binLiftLCA(int u, int v,vector<int> &lvl,vector<vector<int>> &dp,vector<vector<int>> &AL) {
    if (lvl[u] < lvl[v])
        swap(u,v);
    
    int diff = lvl[u] - lvl[v];
    for (int i=0;i<LN;++i) {
        if (diff & 1<<i) //need to jump by this one NOT i but 1<<i
            u = dp[u][i];
    }
    
    
    //now at same level
    
    if (u == v) // DONT FORGET
        return u;
    
    
    for (int i=LN-1;i>=0;--i) {
        if (dp[u][i] != dp[v][i]) { //not the same after jump, so jump both up
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0]; // == dp[v][0] - parent is LCA. 
    
}

int main() {
    int n,m; cin >> n; cin >> m;
    vector<vector<int>> AL(n,vector<int>());
    vector<int> pages(n);
    for (int i=0;i<n;++i) {
        cin >> pages[i];
    }
    for (int j=0;j<m;++j) {
        int u,v;
        cin >> u; cin >> v; --u; --v; 
        AL[u].push_back(v);
    }
    
    vector<bool> visited(n,false);
    vector<int> pagesFromRoot(n,0);
    vector<int> culminatingConcepts;
    
    for (int u=0;u<n;++u) {
        if (!visited[u]) //new connected component
            calcPagesFromRoot(u,pagesFromRoot,pages,visited,AL,0,culminatingConcepts);
    }
    
	//cout << culminatingConcepts.size() << endl;
	
    LN = ceil(log(n)/log(2)); //check
    
    vector<int> lvl(n,0);
    vector<vector<int>> dp(n,vector<int>(LN,-1));
    vector<int> visitedBL(n,0);
    int cc = 1;
    for (int u=0;u<n;++u) {
        if (!visitedBL[u]) //new connected component
            preprocessBinLift(u,lvl,dp,AL,visitedBL,cc);
        ++cc;
    }
    
    //cout << dp << endl;
    
    int minPages = 10000000;
    //all pairs of culminating concepts
    for (int i = 0; i < culminatingConcepts.size();++i) {
        int cO = culminatingConcepts[i];
        for (int j = 0; j < i; ++j) {
            int cI = culminatingConcepts[j];
            int pages;
            if (visitedBL[cO] != visitedBL[cI]) { //different streams (Connected Components)
                pages = pagesFromRoot[cO] + pagesFromRoot[cI];
            } else {
                int LCA = binLiftLCA(cO,cI,lvl,dp,AL);
                pages = pagesFromRoot[cO] + pagesFromRoot[cI] - pagesFromRoot[LCA];
            }
            minPages = min(minPages,pages);
        }
    }
    
    cout << minPages << endl;
}