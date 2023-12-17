#include <bits/stdc++.h>
using namespace std;

inline int MOD(int x, int N) {
    return (x + N) % N;
}

const int UNSEEN = 0;
const int PROCESSING = 1;
const int DONE = 2;

vector<vector<int>> AL;
vector<int> state;
int N, K;

bool dfs(int u, int cnt) {
    if (state[u] == PROCESSING) { // found cycle
        return true;
    } else if (cnt == K) {
        return true;
    } else {
        state[u] = PROCESSING;
        for (int v : AL[u]) {
            if (dfs(v, cnt + 1)) return true;
        }
        state[u] = DONE;
        return false;
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T;++t) {
        cin >> N >> K;
        vector<int> B(N);
        for (int n = 0; n < N; ++n) {
            cin >> B[n];
        }

        AL.assign(N, vector<int>());
        state.assign(N, UNSEEN);
        for (int i = 0; i < N; ++i) {
            // x = right shifts to get it into position
            // connect x to (x - a[i]) % N 
            if (B[i] <= N) {
                int x = MOD(B[i] - (i + 1), N);
                int y = MOD(x - B[i], N);                
                AL[y].push_back(x);
            }

        }

        cout << (dfs(0, 0) ? "Yes" : "No") << endl;
    }
    return 0;
}