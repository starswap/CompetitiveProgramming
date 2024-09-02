#include <bits/stdc++.h>
using namespace std;

int N;
long long S;

bool can(const vector<int>& widths, int mi) {
    int wbucks[3] = {0, 0, 0};
    long long space_needed = 0;
    for (int i = 0; i < mi - 2; ++i) {
        int w = widths[i];
        wbucks[w % 3]++;
        space_needed += w;
    }

    if (wbucks[1] > wbucks[2]) {
        int remaining_1_over = (wbucks[1] - wbucks[2]);
        space_needed += remaining_1_over / 2 + remaining_1_over % 2;
    } else if (wbucks[2] > wbucks[1]) {
        int remaining_2_over = (wbucks[2] - wbucks[1]);
        space_needed += remaining_2_over;
    }

    return space_needed <= S * 3 - 6;
}

int main() {
    cin >> N >> S;
    vector<int> widths(N);
    for (int n = 0; n < N; ++n) {
        cin >> widths[n];
    }

    if (N == 1 || S == 1) {
        cout << 1 << endl; 
    } else {
        sort(widths.begin(), widths.end());
        int lo = 2; // in
        int hi = N + 1; // out
        while (hi - lo > 1) {
            int mi = (lo + hi)/2;
            if (can(widths, mi)) {
                lo = mi;
            } else {
                hi = mi;
            }
        }
        cout << lo << endl;
    }
    return 0;
}