#include <bits/stdc++.h>
using namespace std;

int N, W;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> W;

    int q = 1000;
    int d = (10000 - W > W) ? 1 : -1;

    int w_line = W;
    vector<pair<int, int>> line;
    for (int n = 0 ; n < N/2; ++n) {
        line.emplace_back(w_line, q);
        w_line += d;                  // word count getting worse
        q--;                          // quality getting worse 
    }
    reverse(line.begin(), line.end());

    int w_equal = (10000 - W > W) ? W + N : W - N;
    vector<pair<int, int>> equal;
    for (int i = 0; i < N - N / 2; ++i) {
        equal.emplace_back(w_equal, q); 
        w_equal -= d;                 // word count getting better (still worse than in line)
        q--;                          // quality getting worse
    }

    for (auto [w, q] : equal) {
        cout << w << " " << q << '\n';
    }

    for (auto [w, q] : line) {
        cout << w << ' ' << q << '\n';
    }

    return 0;
}

// This makes:
//     o
//     o
//     o
//     o
//     o
// oooooooooo
