#include <bits/stdc++.h>
using namespace std;

using point = pair<int, int>;
using segment = pair<point, point>;

const double INF = 1e30; 
const int WINDOW_SIZE = 5;

vector<point> points;
map<point, int> remaining_points;
priority_queue<
    tuple<double, point, point>,
    vector<tuple<double, point, point>>,
    greater<tuple<double, point, point>>> best_dists;
map<point, point> other_end;

void setup_best_dists() {

    for (auto it = points.begin(); it != points.end(); ++it) {
        int i = 0;
        // double min_1_dist = INF;
        // double min_2_dist = INF; 
        
        for (auto it2 = next(it); it2 != points.end() && i < WINDOW_SIZE; ++i, ++it2) {
            double dist = hypot(it->first - it2->first, it->second - it2->second);

            // if (dist < min_1_dist) {
                // min_2_dist = min_1_dist;
                // min_1_dist = dist;
                best_dists.push(make_tuple(dist, *it, *it2));
            // } else if (dist < min_2_dist) {
                // min_2_dist = dist;
                // best_dists.push(make_tuple(dist, it - points.begin(), it2 - points.begin()));
            // }

        }
    }
}

tuple<double, point, point> find_closest_two_points() {
    // cout << "starting" << endl;
    while (!best_dists.empty()) {
        auto [dist, p1, p2] = best_dists.top(); best_dists.pop();
        if (remaining_points[p1] && remaining_points[p2] && other_end[p1] != p2) {
            return make_tuple(dist, p1, p2);
        } else {
            // cout << "Skipping " << "(" << p1.first << "," << p1.second << "), (" << p2.first  << ", " << p2.second << ")" << endl;
            // cout << remaining_points[p1] << endl;
            // cout << remaining_points[p2] << endl;
            // cout << "(" << other_end[p1].first << other_end[p1].second << ")" << endl;
        }
    }
    assert(1 == 0);
}

int main() {
    cout << fixed << setprecision(9);

    int N; cin >> N;
    points.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    if (N == 2) {
        cout << hypot(points[0].first - points[1].first, points[0].second - points[1].second) << endl;
    } else {
        best_dists = priority_queue<tuple<double, point, point>, vector<tuple<double, point, point>>, greater<tuple<double, point, point>>>();

        vector<function<int(const point&, const point&)>> lambdas = {
                [](const point& p1, const point& p2){
                    return (p1.first == p2.first) ? (p1.second > p2.second) : (p1.first > p2.first);
                },
                [](const point& p1, const point& p2){
                    return (p1.second == p2.second) ? (p1.first > p2.first) : (p1.second > p2.second);
                },
                [](const point& p1, const point& p2){
                    return (p1.first == p2.first) ? (p1.second < p2.second) : (p1.first > p2.first);
                },
                [](const point& p1, const point& p2){
                    return (p1.second == p2.second) ? (p1.first < p2.first) : (p1.second > p2.second);
                }
        };

        double best_distance = INF;
        for (auto sort_l : lambdas) {
            sort(points.begin(), points.end(), sort_l);
            setup_best_dists();
        }

        for (auto p : points) {
            remaining_points[p] = 2;
        }

        other_end.clear();
        for (auto p : points) {
            other_end[p] = p;
        }

        double distance = 0;
        int n_remaining_points = N;

        while (n_remaining_points > 2) {            
            auto [dist, point_1, point_2] = find_closest_two_points();
            // cout << "Connecting (" << point_1.first << "," << point_1.second << ") to (" << point_2.first << "," << point_2.second << ")" << endl; 
            
            auto oe = other_end[point_1];
            other_end[other_end[point_1]] = other_end[point_2];
            other_end[other_end[point_2]] = oe;
            
            remaining_points[point_1]--;
            remaining_points[point_2]--;
            if (!remaining_points[point_1]) n_remaining_points--;
            if (!remaining_points[point_2]) n_remaining_points--;
            distance += dist;
        }
        cout << distance << endl;
    }

    return 0;
}
