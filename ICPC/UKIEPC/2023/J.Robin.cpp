// Using Robin's method from the solution slides

#include <bits/stdc++.h>
using namespace std;

using point_in_time = double;
using airport_code = string;
using airport_idx = int;
using flight_idx = int;
using vertex = pair<point_in_time, airport_idx>; 

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

map<airport_code, airport_idx> location_to_idx;
vector<flight> flights;
map<vertex, vector<vertex>> AL;
map<vertex, point_in_time> earliest_reach_end;
map<airport_idx, set<point_in_time>> interesting_times;
vector<flight_idx> itinerary_indices;

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
}

void build_graph() {
    for (int n = 0; n < N; ++n) {
        interesting_times[flights[n].airport_start].insert(flights[n].start_time_mins);
        interesting_times[flights[n].airport_end].insert(flights[n].end_time_mins);
        AL[make_pair(flights[n].end_time_mins, flights[n].airport_end)].push_back(make_pair(flights[n].start_time_mins, flights[n].airport_start)); // REVERSED GRAPH
    }

    for (int idx : itinerary_indices) {
        interesting_times[flights[idx].airport_start].insert(flights[idx].start_time_mins + 0.5);
    }

    for (const auto &[airport, points] : interesting_times) {
        for (auto it = points.begin(); it != prev(points.end()); ++it) {
            point_in_time time_1 = *it;
            point_in_time time_2 = *next(it);
            AL[make_pair(time_2, airport)].push_back(make_pair(time_1, airport)); // REVERSED GRAPH
        }
    }
}

void dfs(vertex current, point_in_time end) {
    if (earliest_reach_end.count(current)) return;
    else {
        earliest_reach_end[current] = end;
        for (const vertex& v : AL[current]) {
            dfs(v, end);
        }
    }
}

void compile_earliest_reach_end() {
    for (const point_in_time& time : interesting_times[dest]) {
        dfs(make_pair(time, dest), time);
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
    itinerary_indices.resize(M);
    for (int m = 0; m < M; ++m) {
        scanf("%d", &itinerary_indices[m]);
        itinerary_indices[m]--; // from 0 not 1
        flights[itinerary_indices[m]].start_time_mins -= 0.5;
    }

    point_in_time worst_case_arrival_time = 0;
    point_in_time planned_arrival_time = flights[*itinerary_indices.rbegin()].end_time_mins;
    dest = flights[*itinerary_indices.rbegin()].airport_end;


    build_graph();
    compile_earliest_reach_end();

    for (int m : itinerary_indices) {
        const flight& f = flights[m];
        vertex start_vertex = make_pair(f.start_time_mins + 0.5, f.airport_start);
        if (!earliest_reach_end.count(start_vertex)) {
            worst_case_arrival_time = INF;
        }
        worst_case_arrival_time = max(worst_case_arrival_time, earliest_reach_end[start_vertex]);
    }

    if (worst_case_arrival_time == INF) {
        puts("stranded");
    } else {
        printf("%d\n", (int) round(max(0.0,  worst_case_arrival_time - planned_arrival_time)));
    }
    return 0;
}
