// 100 mins
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N; cin >> N;
    vector<int> deltas(N);
    for (int n = 0; n < N; ++n) {
        cin >> deltas[n];
    }

    priority_queue<int, vector<int>, greater<int>> go_up;
    priority_queue<int, vector<int>, greater<int>> go_down;
    int ac = 0;

    ll total_diff = 0;

    for (int i = 0; i < N; ++i) {
        int diff = i - deltas[i];
        if (diff > 0) {go_up.push(diff);}
        else if (diff < 0) {go_down.push(-diff);}
        else {ac++;}
        total_diff += abs(diff);
    }

    int down = go_down.size();
    int up = go_up.size();

    ll best = total_diff;
    ll old_diff = total_diff;
    int wrong = down + ac;
    for (int i = 1; i < 700005; ++i) { // going up
        total_diff += wrong;
        total_diff -= go_up.size();
        while (!go_up.empty() && i == go_up.top()) {
            go_up.pop();
            wrong++;
        }
        best = min(best, total_diff);
    }

    total_diff = old_diff;
    wrong = up + ac;
    for (int i = 1; i < 700005; ++i) {
        total_diff += wrong;
        total_diff -= go_down.size();
        while (!go_down.empty() && i == go_down.top()) {
            go_down.pop();
            wrong++;
        }
        best = min(best, total_diff);
    }

    cout << best << endl;

    return 0;
}
