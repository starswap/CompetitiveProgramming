#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, M;
set<pair<int, int>> dual_edges;
vector<vector<int>> AL;

void do_BFS() {
    queue<pair<int, int>> q;
    vector<int> visited(N, false);
    q.emplace(0, -1);
    while (!q.empty()) {
        auto [u, p] = q.front(); q.pop();
        for (int v : AL[u]) {
            if (v != p) {
                if (visited[v]) {
                    dual_edges.emplace(min(u, v), max(u, v));
                } else {
                    visited[v] = true;
                    q.emplace(v, u);
                }
            }
        }
    }
}

vector<vector<int>> dp;
int colour_tree(int u, bool parent_is_black, int p, const vector<bool> &base_covering) {
    if (dp[u][parent_is_black] != -1) {
        return dp[u][parent_is_black];
    } else {
        int best_this_black = 0;
        int best_this_white = 1;
        for (int v : AL[u]) {
            if (v != p && !dual_edges.count(make_pair(min(u, v), max(u, v)))) {
                best_this_white = best_this_white + colour_tree(v, false, u, base_covering);
                best_this_black = best_this_black + colour_tree(v, true, u, base_covering);
            }
        }
        int ans = 0;
        if (!parent_is_black || base_covering[u]) {
            ans = best_this_black;
        } else {
            ans = max(best_this_black, best_this_white);
        }
        dp[u][parent_is_black] = ans;
        return ans;
    }
}

int do_colouring() {
    int maxi = 0;
    vector<pair<int, int>> dual_edge_vec(dual_edges.begin(), dual_edges.end());
    int des = dual_edge_vec.size();
    for (int mask = 0; mask < (1 << des); ++mask) {
        vector<bool> base_covering(N, false);
        for (int i = 0; i < des; ++i) {
            base_covering[(mask & (1 << i)) ? dual_edge_vec[i].first : dual_edge_vec[i].second] = true; 
        }

        dp.assign(N, vector<int>(2, -1));
        int score = colour_tree(0, true, -1, base_covering);  
        if (score > maxi) {
            maxi = score;
        }
    }
    return maxi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> N >> M;
    AL.assign(N, vector<int>());
    for (int m = 0; m < M; ++m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }

    do_BFS();
    assert(dual_edges.size() <= 16);
    cout << do_colouring() << endl;
    return 0;
}