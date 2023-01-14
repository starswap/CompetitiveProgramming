#include <bits/stdc++.h>
using namespace std;

const int MAX_NUM = 300000;
int main() {
    int N;
    cin >> N;

    // Sieve largest prime dividing x
    vector<int> lps(MAX_NUM+1,1);
    for (int i=1;i<=MAX_NUM;++i) {
        if (lps[i] != 1) continue;
        for (int j=i;j<=MAX_NUM;j+=i) {
            if (j % i == 0) lps[j] = i;
        }
    }
    // cout << "Phase 1 done" << endl;

    // Build bipartite graph
    vector<vector<int>> AL(MAX_NUM, vector<int>());

    vector<int> spiders(N, -1);
    for (int n=0; n<N; ++n) {
        int a;
        cin >> a;
        spiders[n] = a;
        while (lps[a] != 1) {
            AL[spiders[n]].push_back(lps[a]);
            AL[lps[a]].push_back(spiders[n]);
            a /= lps[a];
        }
    }
    
    // cout << "Phase 2 done" << endl;

    // Do BFS
    queue<pair<int,int>> qu;
    vector<int> parent(MAX_NUM, -1);
    
    int si, ti;
    cin >> si; 
    cin >> ti;
    si--;
    ti--;

    int s = spiders[si];
    int t = spiders[ti];
    
    if (si == ti) {
        cout << 1 << endl;
        cout << si+1 << endl;
    }
    else if (s == t && s != 1) {
        cout << 2 << endl;
        cout << si+1 << " " << ti+1 << endl;
    }
    else {
        qu.emplace(s,1);

        while (!qu.empty()) {
            auto [u, dist] = qu.front(); qu.pop();
            for (int v : AL[u]) {
                if (parent[v] == -1) {
                    qu.emplace(v, dist+1);
                    parent[v] = u;
                }
            }
            if (parent[t] != -1) break;
        }
        
        if (parent[t] == -1) cout << "-1";
        else {
            vector<int> route;
            int v = t;
            bool isVirtual = lps[t] == t; // find(spiders.begin(), spiders.end(),parent[v]) == spiders.end();
            
            while (v != s) {
                if (!isVirtual && v != t)
                    route.push_back(v);
                v = parent[v];
                isVirtual = !isVirtual;
            }
            // if (lps[])
            reverse(route.begin(), route.end());
            cout << route.size() + 2 << endl;
            cout << si+1 << " ";
            for (int u : route) {
                cout << find(spiders.begin(), spiders.end(),u) - spiders.begin() + 1 << " ";
            }
            cout << ti+1;
            cout << endl;
        }
    }

    return 0;
}
