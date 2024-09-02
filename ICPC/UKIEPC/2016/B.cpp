#include <bits/stdc++.h>
using namespace std;

#define double long double

struct point {
    double x;
    double y;
    point():x(0),y(0) {};
    point(double x, double y):x(x),y(y) {};
};

const double INF = 1e60;
const double EPS1 = 1e-6;
const double EPS2 = 1e-6;
constexpr int MAXN = 100005;
const int UNDEF = -10000000;

double area(const vector<point> &pts) {
    double area = 0;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        area += (pts[i].x) * (pts[i+1].y);
        area -= (pts[i+1].x) * (pts[i].y);
    }
    return area / 2;
}

inline double areaDelta(point old, point newP) {
    if (old.x == UNDEF && old.y == UNDEF) return 0;
    return (old.x) * (newP.y) - (newP.x) * (old.y);
}


double twoVertLineArea(double xa, double xb, const vector<point> &pts) {

    double area = 0;
    point prev(UNDEF, UNDEF);
    point first;

    bool setting = false;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        if (setting){
            area += areaDelta(prev, pts[i]);
            if (prev.x == UNDEF) first = pts[i];
            prev = pts[i];
        }

        double y1 = pts[i].y;
        double x1 = pts[i].x;
        double x2 = pts[i+1].x;
        double y2 = pts[i+1].y;

        if (x1 <= xa && xa < x2) {
            point newP(xa, ((y1 + (y2 - y1)/(x2 - x1)*(xa - x1))));
            area += areaDelta(prev, newP);
            if (prev.x == UNDEF) first = newP;
            prev = newP;           
            setting = !setting;
        }

        if (x1 <= xb && xb < x2) {
            point newP(xb, ((y1 + (y2 - y1)/(x2 - x1)*(xb - x1))));
            area += areaDelta(prev, newP);
            if (prev.x == UNDEF) first = newP;
            prev = newP;
            setting = !setting;
        }

        if (x2 <= xb && xb < x1) {
            point newP(xb, ((y1 + (y2 - y1)/(x2 - x1)*(xb - x1))));
            area += areaDelta(prev, newP);
            if (prev.x == UNDEF) first = newP;
            prev = newP;
            setting = !setting;
        }

        if (x2 <= xa && xa < x1) {
            point newP(xa, ((y1 + (y2 - y1)/(x2 - x1)*(xa - x1))));
            area += areaDelta(prev, newP);
            if (prev.x == UNDEF) first = newP;
            prev = newP;
            setting = !setting;
        }

    }

    area += areaDelta(prev, first);
    return area / 2;  
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    double C;
    int N;
    cin >> C >> N;

    deque<point> ptsD;
    double minX = INF;
    double maxX = 0;
    for (int n = 0; n < N; ++n) {
        double x, y;
        cin >> x >> y;
        ptsD.emplace_back(x, y);
        minX = min(x, minX);
        maxX = max(x, maxX);
    }


    // rotate points so that minimum x is at the front
    while (!(minX == ptsD.begin()->x)) {
        auto next = ptsD.front(); ptsD.pop_front();
        ptsD.push_back(next);
    }

    // convert back into vector.
    vector<point> pts(ptsD.begin(), ptsD.end());  

    pts.push_back(pts[0]);

    vector<double> bs;
    bs.push_back(minX); //**
    double totalFoundArea = 0;
    double allArea = area(pts);

    // cout << allArea << endl;

    int i;
    for (i = 1; allArea / i >= C; i ++) {}
    double targ = allArea / (i - 1);

    while (allArea - totalFoundArea - 1.5 * C > -EPS1) {
        double L = *bs.rbegin(); // included
        double R = maxX + 1; // excluded
        while (R - L > EPS2) {
            double M = (L + R) / 2;
            double ar = twoVertLineArea(*bs.rbegin(), M, pts);
            if (ar > targ) {
                R = M;
            }
            else {
                L = M;
            }
        }
        double M = ( L + R ) / 2;
        totalFoundArea += twoVertLineArea(*bs.rbegin(), M, pts);
        bs.push_back(M);
    }
    
    cout << fixed << setprecision(9) << bs.size()  << '\n';
    for (int i = 1; i < bs.size(); ++i) {
        cout << bs[i] << '\n';
    }

    return 0;
}
