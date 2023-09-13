#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<long long> T;

int main() {
    cin >> N >> M >> K;
    T.resize(N);

    for (int n = 0; n < N; ++n) {
        cin >> T[n];
    }

    vector<bool> norway_nodes(N, false);
    int count_norway_nodes = 0;
    if (K > 0) {
        norway_nodes[0] = true;
        count_norway_nodes = 1;
    }

    bool can_direct = false;
    for (int m = 0; m < M; ++m) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (u == 0 && count_norway_nodes < K) { norway_nodes[v] = true; count_norway_nodes++; }
        if (v == 0 && count_norway_nodes < K) { norway_nodes[u] = true; count_norway_nodes++; }
        if ((u == 0 && v == N - 1) || (v == 0 && u == N - 1)) can_direct = true;
    } 

    if (N == 2 && K == 1) { // only impossible case
        cout << "impossible" << endl;
    } else {
        char maxi_char = K > N - K ? 'N' : 'S';
        char mini_char = K > N - K ? 'S' : 'N';
        vector<bool> norway(N, false);
        if (can_direct) { // check if direct  - set the two endpoints the same and the others however you like bc the only shortest path will be direct
            int remaining_maxi_nodes = max(K, N - K) - 2;
            cout << maxi_char;
            for (int n = 1; n < N - 1; ++n) { // set arbitrarily
                if (remaining_maxi_nodes) { cout << maxi_char; remaining_maxi_nodes--; }
                else cout << mini_char;
            } 
            cout << maxi_char;
        } else { // otherwise - start and all start-adj nodes to norway. Everything else is sweden.
            for (int n = 0; n < N; ++n) {
                if (norway_nodes[n]) cout << 'N';
                else if (count_norway_nodes < K) { cout << 'N'; count_norway_nodes++; }
                else cout << 'S';
            } 
        }
    }
    return 0;
}