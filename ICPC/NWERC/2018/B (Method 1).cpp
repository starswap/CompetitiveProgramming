#include <bits/stdc++.h>
using namespace std;

vector<long long> meetingMins;
vector<vector<int>> AL;
vector<int> dependentsLeft;
int N;

long long solve() {
    auto comp = [] (int meeting1, int meeting2) {return meetingMins[meeting1] > meetingMins[meeting2];};
    priority_queue<int, vector<int>, decltype(comp)> availNodes(comp);

    for (int i = 0 ; i < N ;++i) {
        if (dependentsLeft[i] == 0) availNodes.push(i);
    }

    vector<int> order;
    while (!availNodes.empty()) {
        int nextNode = availNodes.top(); availNodes.pop();
        order.push_back(nextNode);

        for (int v : AL[nextNode]) {
            dependentsLeft[v]--;
            if (dependentsLeft[v] == 0) availNodes.push(v);
        }

    }

    reverse(order.begin(), order.end());

    long long maxTime = 0;
    for (long long i = 0; i < N; ++i) {
        maxTime = max(maxTime, i + meetingMins[order[i]]);
    }

    return maxTime;
}

int main() {
    cin >> N;
    meetingMins.assign(N,0);
    dependentsLeft.assign(N, 0);
    AL.assign(N, vector<int>());

    for (int n = 0; n < N; ++n) {
        cin >> meetingMins[n];
        int m; cin >> m;
        for (int i = 0; i < m; ++i) {
            int dep; cin >> dep; dep--;
            AL[n].push_back(dep);
            dependentsLeft[dep]++;
        }
    }

    cout << solve() << endl;

    return 0;
}
