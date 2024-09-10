#include <bits/stdc++.h>
using namespace std;

/* Robin calls the centre of the diameter the centroid of the tree in the video
   solutions and on the slides. This is not the correct term for such a node. */

const int INF = 1000000001;
int N;
vector<vector<int>> AL;

pair<int, int> dfs(int u, int p, int h) {
    int max_d = h;
    int furth = u;

    for (int v : AL[u]) {
        if (v == p) continue;
        auto [d, w] = dfs(v, u, h + 1);
        if (d > max_d) {
            max_d = d;
            furth = w;
        }
    }
    return make_pair(max_d, furth);
}

/* Can do this a little bit more easily by saving
   parents and then constructing a longest path as 
   a vector and then just taking the middle of it. */
int find_or_make_middle(int u, int p, int u2, int d) {
    if (u == u2) return -d;

    for (int v : AL[u]) {
        if (v == p) continue;
        int res = find_or_make_middle(v, u, u2, d + 1);
        if (res == INF) continue;
        if (res >= 0) return res;
        else if (res < 0) {
            int depth = -res;
            if (d * 2 == depth) {
                return u;
            } else if (d * 2 + 1 == depth) {
                AL[u].erase(find(AL[u].begin(), AL[u].end(), v));
                AL[v].erase(find(AL[v].begin(), AL[v].end(), u));
                AL[v].push_back(N);
                AL[u].push_back(N);
                AL.resize(N + 1);
                AL[N].push_back(v);
                AL[N].push_back(u);
                return N++;
            } else {
                return res;
            }
        }
    }
    return INF;
}

int find_middle() {
    auto [d1, u1] = dfs(0, -1, 0);
    auto [d2, u2] = dfs(u1, -1, 0);
    return find_or_make_middle(u1, -1, u2, 0);
}

map<vector<int>, int> children_to_label;
vector<int> node_label;

int make_labels(int u, int p) {
    vector<int> children_labels;
    for (int v : AL[u]) {
        if (v == p) continue;
        children_labels.push_back(make_labels(v, u));
    }
    sort(children_labels.begin(), children_labels.end());
    if (children_to_label.count(children_labels)) {
        node_label[u] = children_to_label[children_labels];
    } else {
        node_label[u] = children_to_label.size();
        children_to_label[children_labels] = node_label[u];
    }
    return node_label[u];
}

int calculate_answer(int u, int p) {
    map<int, int> label_to_signs;
    label_to_signs[node_label[u]] = 1;
    for (int v : AL[u]) {
        if (v == p) continue;
        label_to_signs[node_label[v]] = calculate_answer(v, u);
    }

    int ans = 0;
    for (const auto &[label, signs] : label_to_signs) {
        ans += signs;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    int old_n = N;
    AL.resize(N);
    for (int n = 0; n < N - 1; ++n) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    int c = find_middle();
    bool new_middle = (old_n != N);
    node_label.resize(N);
    children_to_label[vector<int>{}] = 0;
    make_labels(c, -1);

    cout << calculate_answer(c, -1) - (new_middle ? 1 : 0) << endl;
    return 0;
}
