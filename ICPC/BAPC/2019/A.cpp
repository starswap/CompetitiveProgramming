#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> children; // AL without parents
vector<int> matches_played; // a list of the numbers of matches played by leaf nodes, in no particular order

vector<bool> visited;
void set_plays(int u, int a) {
    visited[u] = true;
    bool leaf = true;
    for (int v : children[u]) {
        if (!visited[v]) set_plays(v, a + 1);
        leaf = false;
    }
    if (leaf) {
        matches_played.push_back(a);
    }
}

int get_plays(int u) {
    int max_plays = -1;
    int best_child = 0;
    for (int v : children[u]) {
        int plays = get_plays(v);
        if (plays > max_plays) {
            max_plays = plays;
            best_child = v;
        }
    }

    for (int v : children[u]) {
        if (v != best_child) { // for everyone except the best child we now know how many matches they will play
            set_plays(v, 1);
        }
    }
    return max_plays + 1;
}

int main() {
    int N, K;
    cin >> N >> K;
    
    vector<int> skills(K, 0);
    for (int k = 0; k < K; ++k) {
        cin >> skills[k];
    }

    children.assign(N, vector<int>());
    for (int n = 1; n < N; ++n) {
        int p; cin >> p;
        children[p].push_back(n);
    }

    visited.assign(N, false);
    get_plays(0);
    set_plays(0, 0);

    // Greedily match the best players against the positions that play the most matches
    sort(matches_played.begin(), matches_played.end());
    sort(skills.begin(), skills.end());

    long long answer = 0;
    for (int n = 0; n < K; ++n) {
        answer += (long long) skills[n] * (long long) matches_played[n];
    }

    cout << answer << endl;
    return 0;
}