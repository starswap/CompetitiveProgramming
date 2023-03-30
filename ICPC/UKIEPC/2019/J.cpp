#include <bits/stdc++.h>
using namespace std;

int n, m;
const double PI = 3.14159265358979;
const double INF = 1e9;
const int MAX_N = 100;
const int MAX_M = 100;
vector<int> programmeItems;
vector<int> stations;
double dp[MAX_N][MAX_M]; // programmeitem, stationnumber

double calcDist(double i, double j) {
    double phi = 2 * PI / m;
    int delta = min(abs(i - j), m - abs(i - j));
    double theta =  delta * phi;
    double csquared = 2 - 2 * cos(theta);
    return sqrt(csquared);
}

double doDP(int programmeId, int stationId) {
    if (programmeId == n - 1) { // last ex done.
        return 0.0;
    }
    else if (dp[programmeId][stationId] != INF) {
        return dp[programmeId][stationId];
    }
    else {   
        for (int next = 0; next < m; ++next) {
            if (stations[next] == programmeItems[programmeId + 1]) {
                dp[programmeId][stationId] = min(dp[programmeId][stationId], calcDist(stationId, next) + doDP(programmeId + 1,next));
            }
        }
        return dp[programmeId][stationId];
    }
}

int main() {
    cin >> n;
    programmeItems.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> programmeItems[i];
        programmeItems[i]--;
    }
    cin >> m;
    stations.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        cin >> stations[i];
        stations[i]--;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = INF;
        }
    }

    double minn = INF;
    for (int s = 0; s < m; ++s) {
        if (stations[s] == programmeItems[0]) {
            minn = min(minn, 1.0 + doDP(0, s));
        }
    }

    cout << fixed << setprecision(10) << minn << endl;
    return 0;
}