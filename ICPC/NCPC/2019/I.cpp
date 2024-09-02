#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<bool>> beat;
    beat.assign(N, vector<bool>(N, false));
    for (int n = 1; n < N; ++n) {
        string pts;
        cin >> pts;
        for (int i = 0; i < N; ++i) {
            beat[n][i] = (pts[i] == '1');
            beat[i][n] = (pts[i] != '1');
        }
    }

    vector<int> scores(N, 0);
    for (int n = 0; n < N; ++n) {
        for (int i = 0; i < N; ++i) {
            scores[n] -= beat[i][n];
        }
    }

    int max_losses = 100000000;
    int losses = 0;
    vector<bool> is_left(N, true);
    for (int i = 0; i < N; ++i) {
        max_losses = min(losses, max_losses);
        int best_to_move = 0;

        for (int j = 1; j < N; ++j) {
            if (is_left[j] && scores[j] > scores[best_to_move]) {
                best_to_move = j;
            }
        }

        for (int j = 0; j < N; ++j) {
            scores[j]++;
        }
        for (int j = 0; j < N; ++j) {
            if (best_to_move == j) continue;
            if (is_left[j] && beat[j][best_to_move]) {
                losses++;
            } else if (!is_left[j] && beat[best_to_move][j]) losses--;
        }

        is_left[best_to_move] = false;
    }
    max_losses = max(max_losses, losses);
    cout << max_losses << endl;

    return 0;
}