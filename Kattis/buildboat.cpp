#include <bits/stdc++.h>
using namespace std;

struct point {
    double x;
    double y;
    point():x(0),y(0) {};
    point(double x, double y):x(x),y(y) {};
};

const double INF = 1e18;
const double EPS = 1e-8;

double area(const vector<point> &pts) {
    double area = 0;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        area += (pts[i].x) * (pts[i+1].y);
        area -= (pts[i+1].x) * (pts[i].y);
    }
    return area / 2;
}

double vertLineArea(double x, const vector<point> &pts) {
    vector<point> ptts;
    bool setting = true;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        if (setting){
            ptts.push_back(pts[i]);
        }
        if (pts[i].x <= x && x < pts[i+1].x || pts[i+1].x <= x && x < pts[i].x) {
            double y1 = pts[i].y;
            double x1 = pts[i].x;
            double x2 = pts[i+1].x;
            double y2 = pts[i+1].y;


            ptts.emplace_back(x, ((y1 + (y2 - y1)/(x2 - x1)*(x - x1))));
            setting = !setting;
        }
    }
    ptts.push_back(ptts[0]);
    return area(ptts);     
}


double twoVertLineArea(double xa, double xb, const vector<point> &pts) {
    vector<point> ptts;
    bool setting = false;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        if (setting){
            ptts.push_back(pts[i]);
        }

        double y1 = pts[i].y;
        double x1 = pts[i].x;
        double x2 = pts[i+1].x;
        double y2 = pts[i+1].y;

        if (x1 <= xa && xa < x2) {
            ptts.emplace_back(xa, ((y1 + (y2 - y1)/(x2 - x1)*(xa - x1))));
            setting = !setting;
        }

        if (x1 <= xb && xb < x2) {
            ptts.emplace_back(xb, ((y1 + (y2 - y1)/(x2 - x1)*(xb - x1))));
            setting = !setting;
        }

        if (x2 <= xb && xb < x1) {
            ptts.emplace_back(xb, ((y1 + (y2 - y1)/(x2 - x1)*(xb - x1))));
            setting = !setting;
        }

        if (x2 <= xa && xa < x1) {
            ptts.emplace_back(xa, ((y1 + (y2 - y1)/(x2 - x1)*(xa - x1))));
            setting = !setting;
        }

    }
    ptts.push_back(ptts[0]);
    return area(ptts);     
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
    vector<point> pts;  
    while (!ptsD.empty()) {
        pts.push_back(ptsD.front());
        ptsD.pop_front();
    }

    pts.push_back(pts[0]);

    vector<double> bs;
    bs.push_back(minX); //**
    double totalFoundArea = 0;
    double allArea = area(pts);

    // cout << allArea << endl;

    int i;
    for (i = 1; allArea / i >= C; i ++) {}
    double targ = allArea / (i - 1);
     

    while (allArea - totalFoundArea - 1.5 * C > -EPS) {
        double L = *bs.rbegin(); // included
        double R = maxX + 1; // excluded
        while (R - L > EPS) {
            double M = (L + R) / 2;
            double ar = twoVertLineArea(*bs.rbegin(), M, pts);
            // cout << vertLineArea(M, pts) - totalFoundArea  << endl;
            // cout << twoVertLineArea(*bs.rbegin(), M, pts)<< endl;
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
    
    cout << fixed << setprecision(12) << bs.size()  << endl;// + 1 << endl;
    for (int i = 1; i < bs.size(); ++i) {
        cout << bs[i] << endl;
    }

    return 0;
}
