#include <bits/stdc++.h>
using namespace std;

int H, W;
vector<vector<int>> heights;
vector<tuple<int, int, int>> heightLocs;
vector<vector<bool>> accessible;
int lifts;

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

void do_dfs(int r, int c) {
    accessible[r][c] = true;
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nc >= 0 && nr < H && nc < W && !accessible[nr][nc] && heights[nr][nc] <= heights[r][c]) {
            do_dfs(nr, nc);
        }
    }
}

int main() {
    cin >> H >> W;

    heights.assign(H, vector<int>(W, -1));
    accessible.assign(H, vector<bool>(W, false));

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> heights[i][j];
            heightLocs.emplace_back(heights[i][j], i, j);
            accessible[i][j] = heights[i][j] <= 1;
        }
    }

    sort(heightLocs.begin(), heightLocs.end());
    reverse(heightLocs.begin(), heightLocs.end());

    for (auto &[h, r, c] : heightLocs) {
        if (!accessible[r][c]) {
            accessible[r][c] = true;
            lifts++;
            do_dfs(r, c);
        }
    } 

    cout << lifts << endl;


    return 0;
}