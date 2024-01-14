#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N, M, Q;

pair<int, int> nominated_island;
vector<pair<int, int>> volcanos;
vector<vector<char>> grid;
vector<vector<int>> volc_dists;
vector<vector<bool>> vis;

int dr[] = {0, 0, -1, 1};
int dc[] = {1, -1, 0, 0};
int dr_d[] = {0, 0, -1, 1, 1, 1, -1, -1};
int dc_d[] = {1, -1, 0, 0, 1, -1, 1, -1};


void compute_volc_dists() {
    queue<pair<pair<int, int>, int>> q;
    set<pair<int, int>> visited;
    for (auto coords : volcanos) {
        q.emplace(coords, 0);
        visited.insert(coords);
    }

    while (!q.empty()) {
        auto [coords, dist] = q.front(); q.pop();
        for (int i = 0 ; i < 4; ++i) {
            pair<int, int> new_coords = make_pair(coords.first + dr[i], coords.second + dc[i]);
            if (new_coords.first < N && new_coords.first >= 0 && new_coords.second < M && new_coords.second >= 0 && !visited.count(new_coords)) {
                volc_dists[new_coords.first][new_coords.second] = dist + 1;
                visited.insert(new_coords);
                q.emplace(new_coords, dist + 1);
            }
        }
    }
}

void dfs(int r, int c, int safety) {
    if (r < 0 || r >= N || c < 0 || c >= M || volc_dists[r][c] < safety || vis[r][c] || grid[r][c] == '#')  {return;}
    else {
        vis[r][c] = true;
        for (int i = 0; i < 4; ++i) {
            dfs(r + dr[i], c + dc[i], safety);
        }
    }
}

bool rt_dfs(int r, int c) {
    if (r == 0 || r == N - 1 || c == 0 || c == M - 1) {return false;}
    else {
        bool ok = true;
        vis[r][c] = true; // ok to reuse I think
        for (int i = 0; i < 8; ++i) {
            if (!vis[r + dr_d[i]][c + dc_d[i]]) ok &= rt_dfs(r + dr_d[i], c +  dc_d[i]);
        }
        return ok;
    }
}

bool forms_round_trip() {
    return rt_dfs(nominated_island.first, nominated_island.second);
}

bool can(int r, int c, int safety) {
    vis.assign(N, vector<bool>(M, false));
    dfs(r, c, safety);
    return forms_round_trip();
}

int query(int r, int c) {
    int lo = 0; // in
    int hi = 3 * 1e5; // out

    while (hi - lo > 1) {
        int mi = (hi + lo) / 2;
        if (can(r, c, mi)) {
            lo = mi;
        } else {
            hi = mi;
        }
    }

    return lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M >> Q;
    grid.assign(N, vector<char>(M));
    volc_dists.assign(N, vector<int>(M, 0));
    for (int n = 0 ; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            cin >> grid[n][m];
            if (grid[n][m] == '#') nominated_island = make_pair(n, m);
            else if (grid[n][m] == 'v') volcanos.emplace_back(n, m);
        }
    }

    compute_volc_dists();
    for (int q = 0; q < Q; ++q) {
        int x, y;
        cin >> x >> y;
        cout << query(--x, --y) << endl;
    }
    return 0;
}
