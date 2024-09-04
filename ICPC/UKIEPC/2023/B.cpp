#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> card_taps(M, vector<int>());
    for (int k = 0; k < K; ++k) {
        int p, c;
        cin >> p >> c;
        c--;
        card_taps[c].push_back(p);
    }

    for (int c = 0; c < M; ++c) {
        int score = 0;
        for (int i = 0; i < card_taps[c].size(); i += 2) {
            if (i == card_taps[c].size() - 1) {
                score += 100;
            } else if (card_taps[c][i] == card_taps[c][i + 1]) {
                score += 100;
            } else {
                score += abs(card_taps[c][i + 1] - card_taps[c][i]);
            }
        }
        cout << score << " ";
    }
    cout << endl;
    return 0;
}
