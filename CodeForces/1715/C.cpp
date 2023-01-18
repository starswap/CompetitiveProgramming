#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N, M;
    cin >> N >> M;
    
    vector<int> a(N, 0);
    queue<pair<int, int>> queries;

    for (int i=0;i<N;++i) {
        int x;
        cin >> x;
        queries.emplace(i, x);    
    }

    for (int m=0;m<M;++m) {
        int i, x;
        cin >> i >> x;
        i--;
        queries.emplace(i, x);
    }

    long long ans = N + (N) * (N-1)/2 ;
    int qn = 0;
    while (!queries.empty()) {
        int dl, dr;
        auto [i, x] = queries.front(); queries.pop(); 
        if (i > 0) {
            if (a[i] == a[i-1]) {
                if (x == a[i-1]) {
                    dl = 0;
                }
                else {
                    dl = 1;
                }
            }
            else {
                if (x == a[i-1]) {
                    dl = -1;
                }
                else {
                    dl = 0;
                }
            }
        }
        if (i < N - 1) {
            if (a[i] == a[i+1]) {
                if (x == a[i+1]) {
                    dr = 0;
                }
                else {
                    dr = 1;
                }
            }
            else {
                if (x == a[i+1]) {
                    dr = -1;
                }
                else {
                    dr = 0;
                }
            }
        }

        a[i] = x;
        int k = i + 1;
        
        int dm = dl + dr;
        ans += static_cast<long long>(k - 1) * static_cast<long long>(dl) + static_cast<long long>(N - k) * static_cast<long long>(dr) + static_cast<long long>(k - 1) * static_cast<long long>(N - k) * static_cast<long long>(dm); 
        if (qn >= N) {
        cout << ans << endl;
        }
        qn++;
    }

    return 0;
}