#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());
    ll rest = 0;
    for (int i = 1; i < N; ++i) {
        rest += (ll) A[i];
    }

    ll ans;
    if (A[0] <= 2 * rest) {
        ans = ((ll) A[0] + rest) / 3;
    } else {
        ans = rest;
    }
    cout << ans << endl;

    return 0;
}