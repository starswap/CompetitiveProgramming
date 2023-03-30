#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double INF = 1e19;

/* GEOMETRY */
struct point {
    double x, y;
    point():x(0),y(0) {};
    point(double ax, double ay):x(ax),y(ay) {};
};

struct line {
    point a, b;
    line(point aa, point ab):a(aa),b(ab) {}; 
};

struct vec {
    double dx, dy;
    vec(point a, point b):dx(b.x - a.x),dy(b.y - a.y) {}
};

bool operator < (point a, point b) {
    if (a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}

double norm(vec a) {return sqrt(a.dx*a.dx + a.dy*a.dy);}

double cross(vec a, vec b) {return a.dx*b.dy - a.dy*b.dx;}

double dot(vec a, vec b) {return a.dx*b.dx + a.dy*b.dy;}

double ptToPt(point a, point b) {return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));}

double ptToLine(point p, line l) {
    double d1 = dot(vec(l.a, p), vec(l.b, l.a)) / norm(vec(l.b, l.a));
    double ax = ptToPt(l.a, p);
    return sqrt(ax*ax - d1*d1);
}

double area(const vector<point> &pts) {
    // Shoelace Formula
    double area = 0;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        area += (pts[i].x) * (pts[i+1].y);
        area -= (pts[i+1].x) * (pts[i].y);
    }
    return area / 2;
}

typedef vector<point> polygon; 

double ptToLineSegment(point p, line l) {
    double da = dot(vec(l.a, p), vec(l.a, l.b));
    double db = dot(vec(l.b, p), vec(l.b, l.a));

    if (da > EPS && db > EPS) { // in range
        double d1 = da / norm(vec(l.b, l.a));
        double ax = ptToPt(l.a, p);
        return sqrt(ax*ax - d1*d1);
    }
    else { // out of range
        return min(ptToPt(l.a, p), ptToPt(l.b, p));
    }
}

bool pointInPolygon(point p, polygon poly) {
    bool count = false;
    for (int i = 0; i < poly.size() - 1; ++i) {
        if ((poly[i].y > p.y != poly[i + 1].y > p.y)) {//  && // horizontal ray; check it lies in the vertical bounds of the side
            if (p.x < EPS + (poly[i+1].x - poly[i].x) / (poly[i+1].y - poly[i].y) * (p.y - poly[i].y) + poly[i].x) {
                count = !count;
            }
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);
    
    int N;
    cin >> N;
    vector<int> H_in(N);
    vector<int> H_out(N);

    double minAr = INF;
    int minId = -1;

    double best = INF;
    for (int n = 0; n < N; ++n) {
        double xymin = INF;
        polygon currentPoly;
        cin >> H_out[n];
        cin >> H_in[n];

        int Mi;
        cin >> Mi;

        for (int m = 0; m < Mi; ++m) {
            double x, y;
            cin >> x >> y;
            currentPoly.push_back(point(x,y));
        }
        currentPoly.push_back(currentPoly[0]);

        for (int i = 0; i < Mi; ++i) {
            xymin = min(xymin, ptToLineSegment(point(0,0),line(currentPoly[i], currentPoly[i+1])));
        }
        double H = min(H_in[n], H_out[n]);
        if (pointInPolygon(point(0,0), currentPoly)) {
            if (area(currentPoly) < minAr) {
                minAr = area(currentPoly);
                minId = n;
            }
        }
        best = min(best, sqrt(H*H + xymin*xymin));
    }
    if (minId != -1)
        best = min(best, (double) H_in[minId]); // direct drill down
    else
        best = min(best, (double) H_out[0]);  // If the point is outside of all of the polygons, the best drill-down is the height outside of any of them, which should be equal.
    cout << best << endl;
    return 0;
}
