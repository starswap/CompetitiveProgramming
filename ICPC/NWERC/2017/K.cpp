#include <bits/stdc++.h>
using namespace std;

inline int logn(int x) {
    return __builtin_ctz(x);
}

const int MAXI = 4096;
const int MAXK = 12;

double dp[MAXI][MAXK];

int main() {
    int N;
    cin >> N;
    vector<int> R(N,0);
    for (int i = 0; i < N ; ++i) {
        cin >> R[i];
    }

    sort(++R.begin(), R.end());
    int zInsert = 1;
    while (__builtin_popcount(R.size()) != 1) {
        R.insert(R.begin() + zInsert,0);
        zInsert += 2;
    }


    int P = R.size();

    for (int k = 0; k < logn(P); k++) {
        int s = 1 << (k + 1);
        for (int i = 0; i < P; i++) {
            int l_inc = s * (i / s);
            int r_exc = s * (i / s + 1);
            dp[i][k] = 0.0;

            for (int j = l_inc; j < r_exc; ++j) {
                if (j / (s / 2) == i / (s / 2)) continue;
                // cout << i << " may play" << j << endl;
                int a = R[i];
                int b = R[j];
                double sub = 1;
                // cout << sub  << endl;
                if (k > 0)
                    sub = dp[j][k - 1] * dp[i][k - 1]; 
                // cout << sub << endl;
                if (a == b && b == 0) {
                    a = 1;
                    b = 1;
                }
                dp[i][k] += static_cast<double>(sub) * ( static_cast<double>(a) / static_cast<double>(a + b));
            }
        }
    }

    cout << fixed << setprecision(10);
    cout << dp[0][logn(P) - 1] << endl;


    return 0;
}