#include <bits/stdc++.h>
using namespace std;
// Max flow code thanks to cp-algorithms.com

const int INF = 1000000000;

int V;
vector<vector<int>> capacity, flow;
vector<int> height, excess;

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}

void relabel(int u) {
    int d = INF;
    for (int i = 0; i < V; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < INF)
        height[u] = d + 1;
}

vector<int> find_max_height_vertices(int s, int t) {
    vector<int> max_height;
    for (int i = 0; i < V; i++) {
        if (i != s && i != t && excess[i] > 0) {
            if (!max_height.empty() && height[i] > height[max_height[0]])
                max_height.clear();
            if (max_height.empty() || height[i] == height[max_height[0]])
                max_height.push_back(i);
        }
    }
    return max_height;
}

int max_flow(int s, int t) {
    height.assign(V, 0);
    height[s] = V;
    flow.assign(V, vector<int>(V, 0));
    excess.assign(V, 0);
    excess[s] = INF;
    for (int i = 0; i < V; i++) {
        if (i != s)
            push(s, i);
    }

    vector<int> current;
    while (!(current = find_max_height_vertices(s, t)).empty()) {
        for (int i : current) {
            bool pushed = false;
            for (int j = 0; j < V && excess[i]; j++) {
                if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
                    push(i, j);
                    pushed = true;
                }
            }
            if (!pushed) {
                relabel(i);
                break;
            }
        }
    }

    int max_flow = 0;
    for (int i = 0; i < V; i++)
        max_flow += flow[i][t];
    return max_flow;
}

int main() {
    int N, M;
    cin >> N;
    vector<int> W(N);
    vector<int> L(N);
    for (int n = 0; n < N; ++n) {
        cin >> W[n] >> L[n];
    }
    cin >> M;
    vector<int> T(M);
    for (int m = 0; m < M; ++m) {
        cin >> T[m];
    }

    V = 2 * N + M + 2; // 2 nodes for each crane; plus 1 for each target building, plus mega-sink and mega-source

    capacity.assign(V, vector<int>(V, 0));

    // Mega-source = 0;
    // Mega-sink = 1;
    // then the cranes
    // then the buildings

    for (int i = 0; i < N; ++i) {
        if (W[i] == 0) {
            capacity[0][2*i+2] = 1;
        }

        capacity[2*i+2][2*i+3] = 1;

        for (int j = 0; j < M; ++j) {
            if (L[i] >= T[j]) {
                capacity[2 * i + 3][2 * N + 2 + j] = 1;
            }
        }

        for (int j = 0; j < N; ++j) {
            if (i != j && L[i] >= W[j]) {
                capacity[2 * i + 3][2 * j + 2] = 1;
            }
        }
    }
    for (int j = 0; j < M; ++j) {
        capacity[2 * N + 2 + j][1] = 1;
    }

    if (max_flow(0, 1) < M) {
        cout << "impossible" << endl;
    }
    else {
        for (int j = 0; j < M; ++j) {
            int v = 2 * N + 2 + j;
            vector<int> cranes;
            int i;
            while (i != N) {
                for (i = 0; i < N; ++i) {
                    if (v != 2 * i + 2 && flow[2 * i + 3][v] != 0) {
                        v = 2 * i + 2;
                        break;
                    }
                }
                cranes.push_back(i + 1);
            }
            reverse(cranes.begin(), cranes.end());

            for (i = 1 ; i < cranes.size() - 1; ++i) {
                cout << cranes[i] << " ";
            }
            cout << cranes[i] << endl;
        }
    }

    return 0;
}
