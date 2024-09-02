#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
vector<vector<int>> cs;
vector<int> tree_sizes;
int calculate_tree_sizes(int u) {
    int s = 1;
    for (int c : cs[u]) {
        s += calculate_tree_sizes(c);
    }
    tree_sizes[u] = s;
    return s;
} 

int solve(int u) {
    if (cs[u].size() == 0) { // 1 leaf; no pairs
        return 0;
    } else {
        vector<pair<int, int>> sizes;
        for (int c : cs[u]) {
            sizes.emplace_back(tree_sizes[c], c);
        }
        sort(sizes.begin(), sizes.end());
        reverse(sizes.begin(), sizes.end());
        int bor = 0;
        for (unsigned int i = 1; i < sizes.size(); ++i) {
            bor += sizes[i].first;
        }

        if (bor >= sizes[0].first) { // can pair all the nodes except the root
            return (tree_sizes[u] - 1) / 2;
        } else {
            int spare = sizes[0].first - bor;
            int internal = solve(sizes[0].second);
            spare -= min(spare, internal * 2);
            return (tree_sizes[u] - 1 - spare) / 2;
        }

    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        cs.assign(N, vector<int>());
        tree_sizes.assign(N, 0);
        for (int i = 1; i < N; ++i) {
            int p; cin >> p; p--;
            cs[p].push_back(i);
        }
        calculate_tree_sizes(0);
        cout << solve(0) << endl;
    }
    return 0;
}