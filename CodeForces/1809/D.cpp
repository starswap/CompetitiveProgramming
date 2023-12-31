#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll DEL_SCORE  = 1000000000001;
const ll SWAP_SCORE = 1000000000000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        s = "0" + s; // sentinel to force processing of last run of 1s

        int zeros_after = 0;
        int zeros_adjacent = 0;
        int current_ones = 0;
        ll best = 0;
        for (int i = s.size() - 1; i > -1; --i) {
            if (s[i] == '0') {
                if (current_ones > 0) { // process this run
                    ll optionA = DEL_SCORE * current_ones + best; // delete all of this run
                    ll optionB = (current_ones == 1) ? zeros_adjacent * SWAP_SCORE + (zeros_after - zeros_adjacent) * DEL_SCORE : zeros_after * DEL_SCORE;
                    best = min(optionA, optionB);
                    zeros_adjacent = 0;
                    current_ones = 0;
                }
                zeros_after++;
                zeros_adjacent++;
            } else {
                current_ones++;
            }
        }

        cout << best << endl;
    }
    return 0;
}