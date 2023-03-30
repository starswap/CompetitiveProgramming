#include <bits/stdc++.h>
using namespace std;

map<int, int> costToCount;
vector<int> width;
vector<vector<int>> AL;
vector<bool> visited;
int numNodes = 0;
void dfs(int u) {
    numNodes++; 
    visited[u] = true;
    if (costToCount.count(width[u])) {costToCount[width[u]]++;}
    else {costToCount[width[u]] = 1;}
    
    for (int v : AL[u]) {
        if (!visited[v]) {
            dfs(v);
        }
        
    }
}


int main() {
    int N, M;
    cin >> N >> M;
    width.assign(N,0);
    AL.assign(N, vector<int>());
    for (int n = 0; n < N; ++n) {
        cin >> width[n];
    }

    for (int m = 0; m < M;++m) {
        int a, b;
        cin >> a >> b; 
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }

    visited.assign(N, false);
    int total = 0;
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            costToCount.clear();
            numNodes = 0;
            dfs(i);
            int maxCount = 0;

            for (auto &[cost, count] : costToCount) {
                maxCount = max(count, maxCount);
            }
            total += numNodes - maxCount;
        }
    }
    cout << total << endl;

    return 0;
}
