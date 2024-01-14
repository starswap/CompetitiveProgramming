#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        set<int> noteq;
        int mini = 1;
        int maxi = 1000000000;
    
        for (int n = 0; n < N; ++n) {
            int a, x; cin >> a >> x;
            if (a == 1) {
                mini = max(mini, x);
            } else if (a == 2) {
                maxi = min(maxi, x);
            } else {
                noteq.insert(x);
            }
        }

        int total = maxi - mini + 1;
        for (int i : noteq) {
            if (i >= mini && i <= maxi) {
                total--;
            }
        }

        cout << max(0, total) << endl;


    }
    return 0;
}