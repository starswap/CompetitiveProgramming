#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2 * 10e5;
vector<int> p(MAX_N * 2 + 10);
vector<vector<int>> AL(MAX_N * 2 + 10, vector<int>());

// start from 1
// check the number of nodes in the produced spanning tree
void do_prim() {
    unordered_set<int> tree;
    queue<int> cands;
    tree.insert(1);

    for (int v : AL[1]) {
        fringe.insert(v);
        cands.push(v);
    }

    while (!cands.empty()) {
        int v = cands.top(); cands.pop();
        if ((tree.contains(v))) continue;
        else {
            tree.insert(v);
        }
    }
}

voidu

int main() {

    int N;
    cin >> N;
    for (int n = 0 ; n < N; ++n) { 
        int K; cin >> K;
        int nextN;
        for (int k = 0; k < K; ++k) {
            cin >> nextN;
            AL[n + 1].push_back(nextN);
         }
    }

    do_prim(1);

    dfs_output();

    return 0;
}