#include <bits/stdc++.h>
using namespace std;

int N, K;

const int UNVISITED = 0;
const int SEEN = 1;
const int FINISHED = 2;

vector<int> state;
int cycle_size = 0;
int exempt = 0;

bool cycle_check(const vector<vector<int>> &AL, int u, int p) {
    if (state[u] == FINISHED) {
        return false;
    } else if (state[u] == SEEN) { // cycle
        return true;
    } else {
        state[u] = SEEN;
        for (int v : AL[u]) {
            if (v != p && cycle_check(AL, v, u)) {
                cycle_size += 1;
                return true;
            }
        }
        state[u] = FINISHED;
        return false;
    }
}

pair<bool, bool> cycle_check_all(const vector<vector<int>> &AL) {
    state.assign(K, UNVISITED);
    for (int i = 0; i < K; ++i) {
        if (cycle_check(AL, i, -1)) {
            return make_pair(true, cycle_size == K - exempt);
        }
    }
    return make_pair(false, false);
}

int main() {
    cin >> N >> K;

    set<pair<int, int>> edges;
    vector<int> counts(K, 0);

    // Unique only
    for (int n = 0; n < N; ++n) {
        int a, b;
        cin >> a;
        cin >> b;
        a--;
        b--;
        edges.emplace(min(a, b), max(a, b));
    }

    // count references
    for (auto [a, b] : edges) {
        counts[a] += 1;
        if (a != b) counts[b] += 1;
    }

    vector<vector<int>> AL(K, vector<int>());
    for (auto [a, b] : edges) {
        if (a != b) {
            if (counts[a] == 1 || counts[b] == 1) { // only occurs once - means we can combine the node with another node
                exempt++;
            } else { // needs to be next door
                AL[a].push_back(b);
                AL[b].push_back(a);
            }
        }
        
    }

    for (int i = 0; i < K; ++i) { // ignore all toppings which we don't use
        if (counts[i] == 0) {
            exempt++;
        }
    }

    bool any_above_2 = false;
    for (int a = 0; a < K; ++a) {
        if (AL[a].size() > 2) { any_above_2 = true; } // instant failure
    }

    auto [any_cycle, cycle_with_all] = cycle_check_all(AL);

    cout << (!any_above_2 && (cycle_with_all || !any_cycle) ? "possible" : "impossible") << endl; 

    return 0;
}
