#include <bits/stdc++.h>
using namespace std;

vector<long long> subtreeTime;
vector<int> meetingMins;
vector<vector<int>> AL;
vector<int> depsLeft;
int N;

long long doDP(int u) {
    if (subtreeTime[u] != -1) return subtreeTime[u];
    
    vector<long long> childTimes;
    for (int v : AL[u]) {
        childTimes.push_back(v);
    }

    long long maxi = meetingMins[u];
    sort(childTimes.begin(), childTimes.end());
    reverse(childTimes.begin(), childTimes.end());
    for (int i = 0 ; i < childTimes.size(); ++i) {
        maxi = max(maxi, (long long) childTimes[i] + (long long) i + 1);
    }
    subtreeTime[u] = maxi;
    return subtreeTime[u];
}

long long solve() {
    auto comp = [] (int meeting1, int meeting2) {return subtreeTime[meeting1] < subtreeTime[meeting2];};
    priority_queue<int, vector<int>, decltype(comp)> availNodes(comp);
    for (int i = 0 ; i < N ;++i) {
        if (depsLeft[i] == 0) availNodes.push(i);
    }

    long long maxTime = 0;
    long long numMeetingsDone = 0;
    while (!availNodes.empty()) {
        int nextNode = availNodes.top(); availNodes.pop();
        long long currTime = meetingMins[nextNode] + numMeetingsDone;

        for (int v : AL[nextNode]) {
            depsLeft[v]--;
            if (depsLeft[v] == 0) availNodes.push(v);
        }

        maxTime = max(maxTime, currTime);
        numMeetingsDone++;
    }

    return maxTime;
}

int main() {
    cin >> N;
    meetingMins.assign(N,0);
    depsLeft.assign(N, 0);
    AL.assign(N, vector<int>());
    subtreeTime.assign(N, 0);

    for (int n = 0; n < N; ++n) {
        cin >> meetingMins[n];
        int m; cin >> m;
        for (int i = 0; i < m; ++i) {
            int dep; cin >> dep; dep--;
            AL[dep].push_back(n);
        }
        depsLeft[n] = m;
    }

    for (int i = 0; i < N; ++i) {
        subtreeTime[i] = -1;
    }

    for (int i = 0; i < N; ++i) {
        doDP(i);     
    }

    cout << solve() << endl;

    return 0;
}
