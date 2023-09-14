#include <bits/stdc++.h>
using namespace std;

const int INF = 1'000'000'000;
const int MAX_T = 2 * 86400;
const int MAX_N = 100;

int dp_no_delays[MAX_N + 1][MAX_T + 1];
int dp_with_delays[MAX_N + 1][MAX_T + 1];
int arrival_time_one_train[MAX_N + 1][MAX_T + 1]; // arrival time if we take a train from N at time T
int arrival_time_one_train_with_delay[MAX_N + 1][MAX_T + 1]; // arrival time if we take a train from N at time T in the delayed set
vector<int> start_train_times;

int N, M;

void doDP(int (&dp)[MAX_N + 1][MAX_T + 1], bool with_delays) {
    for (int n = 1; n <= N; ++n) {
        dp[n][MAX_T] = INF;
    }
    for (int t = 0; t <= MAX_T; ++t) {
        dp[N][t] = t;
    }

    for (int n = N - 1; n >= 1; n--) {
        for (int t = MAX_T - 1; t >= 1; t--) {
            int next_arrival = ((with_delays) ? arrival_time_one_train_with_delay : arrival_time_one_train)[n][t];
            if (next_arrival == INF) {
                dp[n][t] = dp[n][t + 1];
            } else {
                dp[n][t] = min(dp[n][t+1], dp[n + 1][next_arrival]);
            }
        }
    }
}
int main() {
    cin >> N >> M;
    for (int i = 0; i <= MAX_N; ++i) {
        for (int j = 0; j <= MAX_T; ++j)  {
            arrival_time_one_train[i][j] = INF;
            arrival_time_one_train_with_delay[i][j] = INF;
        }
    }

    for (int m = 0; m < M; ++m) {
        int start, leave_time, arrive_time, delay;
        cin >> start >> leave_time >> arrive_time >> delay;
        arrival_time_one_train[start][leave_time] = arrive_time;
        arrival_time_one_train_with_delay[start][leave_time + delay] = arrive_time + delay;
        if (start == 1) start_train_times.push_back(leave_time);
    }

    doDP(dp_no_delays, false);
    doDP(dp_with_delays, true);

    sort(start_train_times.begin(), start_train_times.end());
    bool done = false;
    for (int t : start_train_times) {
        if (dp_with_delays[1][t] - dp_no_delays[1][t] >= 1800) {
            cout << t << endl;
            done = true;
            break;
        }
    }

    if (!done) {
        cout << "impossible" << endl;
    }
    return 0;
}