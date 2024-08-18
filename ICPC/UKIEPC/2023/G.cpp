#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const double INF = 1e8;

double S;
int N;

struct point {
    double x, y;
};

struct line_seg {
    point start;
    point end;
};

double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

point interpolate_distance_along(line_seg seg, double distance_along) {
    double full_dist = dist(seg.start, seg.end);
    double fraction = distance_along / full_dist;
    double dx = (seg.end.x - seg.start.x) * fraction;
    double dy = (seg.end.y - seg.start.y) * fraction;
    point result = point{seg.start.x + dx, seg.start.y + dy};
    return result;
}

// Find every time when either the first or second walker switches from one segment to another segment.
// For every gap between these times ternary search to find the minimum distance between the walkers.

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << fixed  << setprecision(8);

    cin >> S >> N;
    vector<point> points(N);

    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // Let p1 be the walker in front
    int p1_i = 0; // index of NEXT node they will reach.
    int p2_i = 1;

    double total_dist = 0;
    double old_total_dist = 0;
    while (total_dist < S + EPS) {
        old_total_dist = total_dist;
        total_dist += dist(points[p1_i], points[p1_i + 1]);
        p1_i++;
    }
    
    point p1 = interpolate_distance_along(line_seg{points[p1_i -1], points[p1_i]}, S - old_total_dist); 
    point p2(points[0]);
    
    vector<pair<point, point>> player_posns;

    // Find which walker will be the next to hit a node
    // Increment that walker's node pointer and add a segment (p1/p2 start/end pair)
    while (p1_i < N) {
        player_posns.emplace_back(p1, p2);

        double p1_to_next_node = dist(p1, points[p1_i]);
        double p2_to_next_node = dist(p2, points[p2_i]);
        if (p1_to_next_node < p2_to_next_node) {
            p1 = points[p1_i];
            p2 = interpolate_distance_along(line_seg{p2, points[p2_i]}, p1_to_next_node);
            p1_i++;
        } else if (fabs(p1_to_next_node - p2_to_next_node) < EPS) {
            p1 = points[p1_i];
            p2 = points[p2_i];
            p1_i++; p2_i++;
        } else {
            p2 = points[p2_i];
            p1 = interpolate_distance_along(line_seg{p1, points[p1_i]}, p2_to_next_node);
            p2_i++;
        }
    }

    player_posns.emplace_back(p1, p2);

    double ans = INF;

    // Ternary search to find the distance along the segments with the closest point
    for (int i = 0; i < player_posns.size() - 1; ++i) {
        auto& [p1_start, p2_start] = player_posns[i];
        auto& [p1_end, p2_end] = player_posns[i+1];

        double lo = 0;
        double hi = dist(p1_start, p1_end);
        double last_value = INF;

        while (hi - lo > EPS) {
            double mi1 = lo + (hi - lo) / 3;
            double mi2 = lo + 2 * (hi - lo) / 3;

            point p1_mi1 = interpolate_distance_along(line_seg{p1_start, p1_end}, mi1);
            point p2_mi1 = interpolate_distance_along(line_seg{p2_start, p2_end}, mi1);
            double dist_mi1 = dist(p1_mi1, p2_mi1); 

            point p1_mi2 = interpolate_distance_along(line_seg{p1_start, p1_end}, mi2);
            point p2_mi2 = interpolate_distance_along(line_seg{p2_start, p2_end}, mi2);
            double dist_mi2 = dist(p1_mi2, p2_mi2);

            if (fabs(dist_mi1 - dist_mi2) < EPS) {lo = mi1; hi = mi2;}
            else if (dist_mi1 < dist_mi2) hi = mi2;
            else lo = mi1;

            last_value = dist_mi1;
        }
        ans = min(ans, last_value);
    }

    cout << ans << endl;
}    
    