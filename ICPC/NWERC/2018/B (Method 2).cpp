#include <bits/stdc++.h>
using namespace std;

vector<long long> meetingMins;
vector<vector<int>> AL;
vector<long long> potentials;
vector<bool> seen;
int N;

void propPots(int u) {
    if (seen[u]) return;
    else {
        seen[u] = true;
        for (int v : AL[u]) {
            propPots(v);
            potentials[u] = min(potentials[u], potentials[v] - 1);
        }
    }
}

long long solve() {

    vector<int> order;
    for (int i = 0; i < N; ++i){ order.push_back(i);}

    sort(order.begin(), order.end(), [](int x, int y) { return potentials[x] < potentials[y]; });

    long long maxTime = 0;
    for (long long i = 0; i < N; ++i) {
        maxTime = max(maxTime, i + meetingMins[order[i]]);
    }

    return maxTime;
}

int main() {
    cin >> N;
    meetingMins.assign(N,0);
    potentials.assign(N, 0);
    AL.assign(N, vector<int>());
    seen.assign(N, false);

    for (int n = 0; n < N; ++n) {
        cin >> meetingMins[n];
        int m; cin >> m;
        potentials[n] = -meetingMins[n];
        for (int i = 0; i < m; ++i) {
            int dep; cin >> dep; dep--;
            AL[dep].push_back(n);
        }
    }
    for (int i = 0; i < N; ++i) {
        propPots(i);
    }
    cout << solve() << endl;

    return 0;
}
