#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


pair<double, double> quad_solve(ll a, ll b, ll c) {
    double sq = sqrt(b * b - 4 * a * c);
    double ans1 = (- b + sq) / (2 * a);
    double ans2 = (- b - sq) / (2 * a);
    return make_pair(ans1, ans2);
}

bool checks(ll a, ll b, ll c, ll x) {
    return (a * x * x + b * x + c == 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        map<int, long long> A;
        for (int i = 0; i < N; ++i) {
            int x; cin >> x;
            A[x]++;
        }
        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            long long x,y; cin >> x >> y;
            auto [ans1, ans2] = quad_solve(1, -x, y);
            if (checks(1, -x, y, round(ans1))) {
                int x1 = round(ans1);
                int x2 = round(ans2);
                if (x1 == x2) {
                    cout << ( A[x1] * (A[x1] - 1)) / 2 << " ";
                } else {
                    cout <<  A[x1] * A[x2] << " ";
                }
            } else {
                cout << 0 << " ";
            } 
        }
        cout << endl;

    }
    return 0;
}