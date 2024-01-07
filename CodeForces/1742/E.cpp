#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N, 0);
        for (int n = 0; n < N; ++n) {
            cin >> A[n];
        }

        vector<ll> total(N + 1, 0);
        vector<int> maxi(N + 1, 0);
        for (int i = 1; i < N + 1; ++i) {
            total[i] = total[i - 1] + A[i - 1];
            maxi[i] = max(maxi[i - 1], A[i - 1]);
        }

        for (int q = 0; q < Q; ++q) {
            int k; cin >> k;
            int lo = 0; // included
            int hi = N + 1; // excluded

            while (hi - lo > 1) {
                int mi = (hi + lo) / 2;
                if (k >= maxi[mi]) { // can do mi
                    lo = mi;
                } else { // can't do mi 
                    hi =  mi;
                }
            }         
            // answer will be the index so that total is the answer
            cout << total[lo] << " ";
        }
        cout << endl;
    }
    return 0;
}
