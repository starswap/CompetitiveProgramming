#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
int N, K;
vector<vector<pair<int, int>>> AL;
vector<int> par;
vector<int> pw;
vector<int> dist;
vector<int> nodes;

const int UNDEF = 1'000'000;
const int INF   = 1'000'000'010;

void get_distances(int u, int d, int p, int i) {
    dist[u] = d;
    nodes[u] = i;
    par[u] = p;
    for (auto [v, w] : AL[u]) {
        if (v == p) continue;
        pw[v] = w;
        get_distances(v, d + w, u, i + 1);
    }
}

int furthest_node(int u) {
    dist.assign(N, 0);
    nodes.assign(N, 0);
    get_distances(u, 0, -1, 0);

    int best = 0;
    int bestI = 0;
    for (int i = 0; i < N; ++i) {
        if (dist[i] > best) {
            best = dist[i];
            bestI = i;
        }
    }
    return bestI;
}

set<int> path_pts;
bool path_centre(int u, int p, int v, int total, int used, int &c1, int &c2) {
    if (u == v) {path_pts.insert(v); return true;}
    for (auto [i, w] : AL[u]) {
        if (i == p) continue;
        if (path_centre(i, u, v, total, used + w, c1, c2)) {
            if (used <= total / 2 && used + w > total / 2) {
                c1 = u;
                c2 = i;
            }
            path_pts.insert(u);
            return true;
        }
    }
    return false;
}

int compute_maxdist(int u, int p, int d) {
    if (path_pts.count(u)) d = 0;
    int maxdist = d;
    for (auto [v, w] : AL[u]) {
        if (v == p) continue;
        maxdist = max(maxdist, compute_maxdist(v, u, d + w));
    }
    return maxdist;
}

tuple<int, int, vector<int>> get_centre() {
    int u = furthest_node(0);
    int v = furthest_node(u);
    int c1 = UNDEF;
    int c2 = UNDEF;
    path_centre(u, -1, v, dist[v], 0, c1, c2);
    return make_tuple(u, v, vector<int>({c1, c2}));
}

int solve() {
    auto [u, v, cs] = get_centre();
    if (cs[0] == UNDEF && cs[1] == UNDEF) return 0;

    int ans = INF;
    for (int c : cs) {
        assert (c != UNDEF);
        int maxdist = compute_maxdist(c, -1, 0);
        int p1 = u;
        int p2 = v;
        int d1 = 0;
        int d2 = 0;
        get_distances(c, 0, -1, 0);
        int M = nodes[u] + nodes[v] + 1;
        while (M > K) {
            if (p2 != c && (p1 == c || d1 + pw[p1] > d2 + pw[p2])) {
                d2 += pw[p2];
                p2 = par[p2];
                M--;
            } else if (p1 != c) {
                d1 += pw[p1];
                p1 = par[p1];
                M--;
            }
        }
        ans = min(ans, max(maxdist, max(d1, d2)));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    AL.resize(N);
    par.resize(N);
    pw.resize(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        AL[u].emplace_back(v, w);
        AL[v].emplace_back(u, w);
    }

    cout << solve() << endl;

    return 0;
}
