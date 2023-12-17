#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> numbers(N);
        for (int n = 0; n < N; ++n) {
            cin >> numbers[n];
        }
        deque<pair<int, int>> comp;
        set<int> unseen;
        for (int i = 0; i <= N; ++i) {
            unseen.insert(i);
        }

        vector<int> mexes(N);
        for (int i = 0; i < N; ++i) {
            int n = numbers[i];
            unseen.erase(n);
            mexes[i] = *unseen.begin();
        }

        int prev = mexes[0];
        int cnt = 1;
        for (int i = 1; i < N; ++i) {
            if (prev != mexes[i]) {
                comp.emplace_back(prev, cnt);
                prev = mexes[i];
                cnt = 1;
            } else {
                cnt++;
            }
        } 
        comp.emplace_back(prev, cnt);

        ll score = 0;
        
        for (int i = 0; i < N; ++i) {score += (ll) mexes[i];}
        ll best_score = score;

        int K = 0;
        for (int i = 0; i < N - 1; ++i) {
            // take off the first one
            auto &[mex, cnt] = comp.front();
            cnt--;
            score -= mex;
            int number = numbers[K];

            int total_count = 0;
            while (!comp.empty() && comp.back().first > number) {
                total_count += comp.back().second;
                score -= (ll) comp.back().first * (ll) comp.back().second;
                comp.pop_back();
            }

            comp.emplace_back(number, total_count);
            score += (ll) number * (ll) total_count;

            comp.emplace_back(N, 1);
            score += N;
            if (cnt == 0) comp.pop_front();
            best_score = max(score, best_score);
            K++;
        }

        cout << best_score << endl;
        
    }
    return 0;
}