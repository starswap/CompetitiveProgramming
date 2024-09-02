#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

struct point {
    double x, y;
    point(double _x, double _y) {x = _x; y = _y;}
};
double dist(point p, point q) {
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

pair<double, double> solve_quadratic(double a, double b, double c) {
    return make_pair((-b + sqrt(b * b - 4 * a * c)) / (2 * a), (-b - sqrt(b * b - 4 * a * c)) / (2 * a));
}

vector<point> get_tangent_ints(point p, double r) {
    double x = p.x;
    double y = p.y;
    auto [tx1, tx2] = solve_quadratic(x * x + y * y, - 2 * r * r * x, r * r * r * r - y * y * r * r);
    auto [ty1, ty2] = solve_quadratic(x * x + y * y, - 2 * r * r * y, r * r * r * r - x * x * r * r);
    if (fabs(x * tx1 + y * ty1 - r * r) < EPS && fabs(x * tx2 + y * ty2 - r * r) < EPS ) return {point(tx1, ty1), point(tx2, ty2)};
    else return {point(tx1, ty2), point(tx2, ty1)};
}

double arc_length(point p, point q, double r) {
    double a = dist(point(0, 0), p);
    double b = dist(point(0, 0), q);
    double c = dist(p, q);
    double theta = acos((a * a + b * b - c * c) / (2 * a * b));
    return r * theta;
}

int main() {
    int xc, yc;
    int xd, yd;
    int x, y, r;
    cin >> xc >> yc >> xd >> yd >> x >> y >> r >> x >> y >> r;

    xc -= x;
    yc -= y;

    xd -= x;
    yd -= y;

    vector<point> tangC = get_tangent_ints(point(xc, yc), r);
    vector<point> tangD = get_tangent_ints(point(xd, yd), r);

    point c(xc, yc);
    point d(xd, yd);
    double best = 1e30;
    for (point p : tangC) {
        for (point q : tangD) {
            best = min(best, dist(c, p) + arc_length(p, q, r) + dist(q, d));
        }
    }
    cout << fixed << setprecision(10) << best << endl;
    return 0;
}