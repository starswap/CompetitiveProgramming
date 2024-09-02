#include <bits/stdc++.h>
using namespace std;

using point_in_time = int;
using airport_code = string;
using airport_idx = int;
using flight_idx = int;

struct flight {
    point_in_time start_time_mins;
    point_in_time end_time_mins;
    airport_idx airport_start;
    airport_idx airport_end;
};

const int INF = 1'000'000'000;
const flight_idx ANY = -1;

int N, M;
airport_idx dest;

map<airport_code, point_in_time> location_to_idx;
map<airport_idx, map<point_in_time, vector<int>>> flights_at_loc_time;
vector<flight> flights;
map<tuple<point_in_time, airport_idx, flight_idx>, point_in_time> DP;

pair<airport_idx, point_in_time> read_endpoint() {
    char s[20];
    int days, hours, mins;
    scanf("%s %dd%d:%d", s, &days, &hours, &mins);
    if (!location_to_idx.count(s)) {
        location_to_idx[s] = location_to_idx.size();
    }

    return make_pair(location_to_idx[s], days * 24 * 60 + hours * 60 + mins); 
}

flight read_flight() {
    auto [start_aiport, start_time] = read_endpoint();
    auto [end_airport, end_time] = read_endpoint();
    flight f{start_time, end_time, start_aiport, end_airport};
    return f;
}

void add_flight(flight f) {
    flights.push_back(f);
    flights_at_loc_time[f.airport_start][f.start_time_mins].push_back(flights.size() - 1);
}

// dp[time][location][flight can't take or ANY] = min(
//      for each flight at this time: if can take: dp[arrival_time][destination][ANY],
//      dp[time of next leaving flight here][location][ANY],
// )

int doDP(point_in_time time, airport_idx location, flight_idx cant_take) {
    auto config = make_tuple(time, location, cant_take);
    if (DP.count(config)) return DP[config];
    
    point_in_time& dp_result = DP[config];
    if (location == dest) { dp_result = time; return dp_result; }
    else {
        dp_result = INF;
        for (flight_idx fi : flights_at_loc_time[location][time]) {
            if (fi != cant_take) {
                dp_result = min(dp_result, doDP(flights[fi].end_time_mins, flights[fi].airport_end, ANY));
            }
        }

        auto it = flights_at_loc_time[location].upper_bound(time);
        if (it != flights_at_loc_time[location].end()) {
            point_in_time leaving = it->first;
            dp_result = min(dp_result, doDP(leaving, location, ANY));
        }
        return dp_result;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    scanf("%d", &N);
    
    for (int n = 0; n < N; ++n) {
        flight f = read_flight();
        add_flight(f);
    }    

    scanf("%d", &M);
    vector<flight_idx> itinerary_indices(M);
    for (int m = 0; m < M; ++m) {
        scanf("%d", &itinerary_indices[m]);
        itinerary_indices[m]--; // from 0 not 1
    }

    point_in_time worst_case_arrival_time = 0;
    point_in_time planned_arrival_time = flights[*itinerary_indices.rbegin()].end_time_mins;
    dest = flights[*itinerary_indices.rbegin()].airport_end;

    for (int m : itinerary_indices) {
        worst_case_arrival_time = max(worst_case_arrival_time, doDP(flights[m].start_time_mins, flights[m].airport_start, m));
    }

    if (worst_case_arrival_time == INF) {
        puts("stranded\n");
    } else {
        printf("%d", max(0,  worst_case_arrival_time - planned_arrival_time));
    }
    return 0;
}
