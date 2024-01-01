#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int x = N * 10;
    multiset<int> spares;
    for (int i = 0; i < N; ++i) {
        spares.insert(x - i - A[i]);
    }

    int best = x - *spares.begin();
    for (int i = 1; i < N; ++i) {
        int oldIMinusOne = x - A[i - 1];
        int newIMinusOne = x - (N - i) - A[i - 1];
        int oldI         = x - i - A[i];
        int newI         = x - A[i];
        spares.erase(spares.find(oldIMinusOne));
        spares.erase(spares.find(oldI));
        spares.insert(newIMinusOne);
        spares.insert(newI);
        best = min(best, x - *spares.begin());
    }

    cout << best << endl;
    return 0;
}