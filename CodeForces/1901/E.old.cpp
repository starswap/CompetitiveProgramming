#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// long long
// look at answer


const int MAX_N = 500000;
const int INF = 1000000010;
const int UNDEF = -INF;
int DP[MAX_N][2];
int A[MAX_N];
vector<vector<int>> tree;
map<int, int> jcts; // from top node to jct
int N;
set<int> seen_jcts;
map<int, int> top_node_parent;

void find_jcts(int u, int p, int top_node) {
    top_node_parent[u] = top_node;
    if (tree[u].size() >= 3) { // found jct
        jcts[top_node] = u;
        for (int v : tree[u]) {
            if (v == p) continue;
            find_jcts(v, u, v);
        }
    } else {
        for (int v : tree[u]) {
            if (v == p) continue;
            find_jcts(v, u, top_node);
        }
    }
}

void clear_dp() {
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < 2; ++j) {
            DP[i][j] = UNDEF;
        }
    }

}

pair<int, int> get_best_two(int u, int p) {
    for (int v : tree[u]) {
        if (v == p || seen_jcts.count(v)) continue;
        auto [best, snd] = get_best_two(v, u);
        if (A[u] >= best) return make_pair(A[u], best);
        else if (A[u] >= snd) return make_pair(best, A[u]);
        else return make_pair(best, snd);
    }
    return make_pair(A[u], -INF);
}

// Never deletes the whole tree
int dp(int u, bool can_delete_from_top) {
    if (DP[u][can_delete_from_top] == UNDEF) {
        int ans = -INF;
        if (!jcts.count(u)) { // is a line
            auto [best, snd] = get_best_two(u, -1);
            if (can_delete_from_top) {ans = best + max(0, snd);}
            else {ans = best;}
        } else {
            int j = jcts[u];
            seen_jcts.insert(j);
            if (can_delete_from_top) {
                // keep this junction
                vector<int> keep_scores;
                for (int c : tree[j]) {
                    keep_scores.push_back(dp(c, false));
                }
                sort(keep_scores.begin(), keep_scores.end());
                reverse(keep_scores.begin(), keep_scores.end());

                int numberPosOrZero = 0;
                int sumPosOrZero = 0;
                int extraSum = 0;
                int extraNumber = 0;
                for (int i : keep_scores) {
                    if (extraNumber + numberPosOrZero == 3) break;
                    if (i < 0) {
                        extraSum += i;
                        extraNumber++;
                    } else {
                        numberPosOrZero++;
                        sumPosOrZero += i;
                    }
                }

                if (numberPosOrZero >= 3) {
                    ans = max(ans, A[j] + sumPosOrZero);
                } else if (numberPosOrZero == 0) {
                    ans = max(ans, A[j]);
                } else if (numberPosOrZero == 1) { // sumPosOrZero is either 0, 1, 2
                    ans = max(ans, A[j] + sumPosOrZero);
                } else {
                    ans = max(ans, A[j] + sumPosOrZero + extraSum); // keep enough to keep centre alive 
                    ans = max(ans, sumPosOrZero); // don't 
                }

                // remove this junction and just pick one of the children
                for (int c : tree[j]) {
                    ans = max(ans, dp(c, true));
                }
            } else {
                
                // take best on this line by way of deleting the junction
                auto [best, snd] = get_best_two(u, -1);
                // best = max(best, A[j]);
                // if (A[j] >= best) {snd = best; best = A[j];}
                // else if (A[j] >= snd) {snd = A[j];}
                ans = max(ans, best);

                // keep this junction
                vector<int> keep_scores;
                int have_to_keep = UNDEF;
                for (int c : tree[j]) {
                    if (top_node_parent[c] == u || ) {
                        have_to_keep = dp(c, false);
                    } else {
                        keep_scores.push_back(dp(c, false));
                    }
                }
                sort(keep_scores.begin(), keep_scores.end());
                reverse(keep_scores.begin(), keep_scores.end());

                int numberPosOrZero = 0;
                int sumPosOrZero = 0;
                int extraSum = 0;
                int extraNumber = 0;
                for (int i : keep_scores) {
                    if (extraNumber + numberPosOrZero == 2) break;
                    if (i < 0) {
                        extraSum += i;
                        extraNumber++;
                    } else {
                        numberPosOrZero++;
                        sumPosOrZero += i;
                    }
                }

                if (numberPosOrZero >= 2) {
                    ans = max(ans, A[j] + sumPosOrZero + have_to_keep);
                } else if (numberPosOrZero == 0) {
                    ans = max(ans, A[j]);
                } else if (numberPosOrZero == 1) { // sumPosOrZero is either 0, 1, 2
                    ans = max(ans, A[j] + sumPosOrZero + extraSum); // keep enough to keep centre alive 
                    ans = max(ans, sumPosOrZero); // don't 
                }
            }
            seen_jcts.erase(j);
        }
        DP[u][can_delete_from_top] = ans;
    }
    return DP[u][can_delete_from_top];
}


void solve() {
    int l; // starting leaf
    for (l = 0; l < N; ++l) {
        if (tree[l].size() == 1) break;
    }
    find_jcts(l, -1, l);
    clear_dp();
    cout << max(0, dp(l, true)) << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        tree.assign(N, vector<int>());
        for (int i = 0; i < N - 1; ++i) {
            int u, v; cin >> u >> v;
            u--; v--;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        solve();
    }
    return 0;
}