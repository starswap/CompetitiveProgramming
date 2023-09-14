#include <bits/stdc++.h>
using namespace std;

const int INF = 1'000'000'000;

vector<set<pair<int, int>>> normal_trains; // arrival, departure
vector<set<pair<int, int>>> delayed_trains; // arrival, departure
vector<tuple<int, int, int, int>> start_trains;

int N, M;

int get_best_final_time(int station, int time_of_arrival, vector<set<pair<int, int>>>& trains) {
    if (station == N) {
        return time_of_arrival;
    } else {
        int next_station_time = INF;
        while (trains[station].size() >= 1) {
            auto [arrive_time, leave_time] = *trains[station].begin();
            if (leave_time < time_of_arrival) { // missed the train!
                trains[station].erase(trains[station].begin());
            } else {
                next_station_time = arrive_time; break;
            }
        }
        if (next_station_time == INF) return INF;
        else return get_best_final_time(station + 1, next_station_time, trains); 
    }
}

int main() {
    cin >> N >> M;
    normal_trains.resize(N);
    delayed_trains.resize(N);


    int start_train_idx = 0;
    for (int m = 0; m < M; ++m) {
        int start, leave_time, arrive_time, delay;
        cin >> start >> leave_time >> arrive_time >> delay;
        if (start == 1) {
            start_trains.emplace_back(arrive_time, leave_time, delay, start_train_idx);
            start_train_idx++;
        } else {
            normal_trains[start].emplace(arrive_time, leave_time);
        }
        delayed_trains[start].emplace(arrive_time + delay, leave_time + delay);
    }

    vector<int> undelayed(start_train_idx);
    vector<int> delayed(start_train_idx);

    
    sort(start_trains.begin(), start_trains.end());
    for (auto &[arrive, leave, delay, train_idx] : start_trains) {
        undelayed[train_idx] = get_best_final_time(2, arrive, normal_trains);
    }
    sort(start_trains.begin(), start_trains.end(), [](tuple<int, int, int, int> train1, tuple<int, int, int, int> train2) {
        return get<1>(train1) < get<1>(train2);
    });
    for (auto &[arrive, leave, delay, train_idx] : start_trains) {
        delayed[train_idx] = get_best_final_time(1, leave, delayed_trains);
    }


    int ans = INF;
    for (auto &[arrive, leave, delay, train_idx] : start_trains) {
        if (delayed[train_idx] - undelayed[train_idx] >= 1800) {
            ans = min(ans, leave);
        }
    }

    if (ans == INF) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}