#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> a(N);
        vector<int> b(N);
        a[0] = 1;
        for (int n = 1; n < N; ++n) {
            cin >> a[n];
        }
        for (int n = 0; n < N; ++n) {
            cin >> b[n];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int shifts = 0;
        for (int n = 0; n < N; ++n) {
            int thisShift = upper_bound(b.begin(), b.end(), a[n]) - b.begin() - n; // i thi right?
            shifts = max(shifts, thisShift);
        }
        cout << shifts << endl;
    }
   return 0;
}