#include <bits/stdc++.h>
using namespace std;

int yellow_per_row = 0;
int N, M;

const int MAXN = 105; // max nodes on each side
const int MAXM = 10105; // max edges
using pi = pair<int, int>;

struct edge_color { // must use 1-based
	int deg[2][MAXN];
	pi has[2][MAXN][MAXN];
	int color[MAXM];
	int c[2];
	void clear(int n){
		for(int t=0; t<2; t++){
			for(int i=0; i<=n; i++){
				deg[t][i] = 0;
				for(int j=0; j<=n; j++){
					has[t][i][j] = pi(0, 0);
				}
			}
		}
	}
	void dfs(int x, int p) {
		auto i = has[p][x][c[!p]];
		if (has[!p][i.first][c[p]].second) dfs(i.first,!p);
		else has[!p][i.first][c[!p]] = pi(0,0);
		has[p][x][c[p]] = i;
		has[!p][i.first][c[p]] = pi(x,i.second);
		color[i.second] = c[p];
	}
	int solve(vector<pi> v, vector<int> &cv){ // cv is colour of 
		int m = v.size();
		int ans = 0;
		for (int i=1;i<=m;i++) {
			int x[2];
			x[0] = v[i-1].first;
			x[1] = v[i-1].second;
			for (int d=0;d<2;d++) {
				deg[d][x[d]]+=1;
				ans = max(ans,deg[d][x[d]]);
				for (c[d]=1;has[d][x[d]][c[d]].second;c[d]++);
			}
			if (c[0]!=c[1]) dfs(x[1],1);
			for (int d=0;d<2;d++) has[d][x[d]][c[0]] = pi(x[!d],i);
			color[i] = c[0];
		}
		cv.resize(m);
		for(int i=1; i<=m; i++){
			cv[i-1] = color[i];
			color[i] = 0;
		}
		return ans;
	}
} EC;

int main() {
    cin >> N >> M;
    vector<vector<bool>> isY(N + 1, vector<bool>(M, false));
    vector<int> yellow_counts_by_column(M, 0);
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            char c; cin >> c;
            if (c == 'Y') {
                isY[n][m] = true;
                yellow_counts_by_column[m]++;
                if (n == 0) yellow_per_row++;
            }
        }
    }
    int T; cin >> T;

    vector<pi> edges;
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            if (isY[n][m]) {
                edges.emplace_back(n + 1, m + 1);
            }
        }
    }

    vector<pair<int, int>> col_and_yellow_counts;
    for (int m = 0; m < M; ++m) {
        col_and_yellow_counts.emplace_back(yellow_counts_by_column[m], m + 1);
    }

    sort(col_and_yellow_counts.begin(), col_and_yellow_counts.end());

    for (int i = 0; i < yellow_per_row; i++) {
        edges.emplace_back(N + 1, col_and_yellow_counts[i].second);
        isY[N][col_and_yellow_counts[i].second - 1] = true;
    }

    vector<int> cols_res;
    edge_color e;
    
    int ans = e.solve(edges, cols_res);
    if (ans > yellow_per_row) {
        cout << "Bugged!" << endl;
    } else {
        vector<vector<int>> res(N + 1, vector<int>(M));
        int c = yellow_per_row + 1;
        for (int n = 0; n < N + 1; ++n) {
            for (int m = 0; m < M; ++m) {
                if (!isY[n][m]) {
                    res[n][m] = c++;
                }
            }
        }
        for (int i = 0; i < edges.size(); ++i) {
            auto [n, m] = edges[i]; n--; m--;
            int colour = cols_res[i];
            res[n][m] = colour;
        }

        if (c - 1 > T) {
            cout << "Bugged!" << endl;
        } else {
            for (int n = 0; n < N + 1; ++n) {
                for (int m = 0; m < M; ++m) {
                    cout << res[n][m] << " ";
                }
                cout << endl;
            }
        }
    }

    return 0;
}
