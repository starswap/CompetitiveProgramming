#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N; cin >> N;
    vector<tuple<int, int, string>> teams(N);
    for (int n = 0; n < N; ++n) {
        string C; int P;
        vector<int> E(6);
        cin >> C >> P;
        for (int i = 0; i < 6; ++i) {
            cin >> E[i];
        }
        sort(E.begin(), E.end());
        int Prog = 10 * P;
        int Tramp = 0;
        for (int i = 1; i < 5; ++i) {
            Tramp += E[i];
        }
        int score = Tramp + Prog;

        teams[n] = make_tuple(score, -n, C);
    }
    sort(teams.begin(), teams.end());
    reverse(teams.begin(), teams.end());

    int total_better = 0;
    int total_same = 1;
    for (int j = 0; j < min(1000, (int) teams.size()); j++) {
        auto [score, i, C] = teams[j];
        if (j > 0) {
            if (score == get<0>(teams[j - 1])) {
                total_same++;
            } else if (score < get<0>(teams[j - 1])) {
                total_better += total_same;
                total_same = 1;
            }
        }
        if (total_better > 2) {
            break;
        }
        cout << C << " " << score << endl;
    }    
    return 0;
}