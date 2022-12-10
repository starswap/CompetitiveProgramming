#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
const int MAX_N = 300001;
int dp[MAX_N];

int treeSize(int u, int p) {
    int s = 1;
    for (int v: AL[u]) {
        if (v != p)
            s += treeSize(v,u);
    }
    dp[u] = s;
    return s;
}

int solve(int u, int p) {


    if (AL[u].size() == 1) {
        return 0;
    }
    else if (AL[u].size() == 2)  {
        int subTree = 0;
        for (int v : AL[u]) {
            if (v == p) continue;
            subTree = dp[v] - 1;
        }
        return subTree;
    }
    else if (AL[u].size() == 3) {
        vector<int> children;
        for (int v : AL[u]) {
            if (v == p) continue;
            children.push_back(v);
        }
        return max(dp[children[0]]-1 + solve(children[1],u), dp[children[1]]-1 + solve(children[0],u));
    }
    else {
        cout << "Fail"  << endl;
        return -1;
    }
}


int main() {
    int T;
    scanf("%d",&T);
    for (int t=0;t<T;++t) {
        int n;
        scanf("%d",&n);
        AL.assign(n,vector<int>());
        for (int i=0;i<n-1;++i) {
            int x,y;
            cin >> x >> y;
            x--; y--;
            AL[x].push_back(y);
            AL[y].push_back(x);
        }
        AL[0].push_back(-1);
        treeSize(0,-1);
        cout << solve(0,-1) << endl;
    }
    return 0;
}