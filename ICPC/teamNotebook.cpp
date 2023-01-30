#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double INF = 1e19;

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

bool ccw(point x, point y, point z) { return cross(vec(x,y),vec(y,z)) > EPS; }

vector<point> CH(vector<point> &pts) {
    int n = pts.size();
    vector<point> H(n + 1);
    int k = 0;

    sort(pts.begin(), pts.end());
    for (int i = 0; i < n; ++i) {
        while ((k >= 2) && !ccw(H[k-2], H[k-1], pts[i])) k--;
        H[k] = pts[i]; k++; 
    }

    for (int t = k + 1, i = n - 2; i >= 0; --i) {
        while ((k >= t) && !ccw(H[k-2], H[k-1], pts[i])) k--;
        H[k] = pts[i]; k++; 
    }

    H.resize(k);
    return H;
}

int lis(const vector<int>& xs) {
    int n = xs.size();
    int k = 0;
    vector<int> endValLengthL(n, 0);
    vector<int> endIdxLengthL(n, 0);

    for (int i = 0; i < n; ++i) {
        int l = lower_bound(endValLengthL.begin(), endValLengthL.begin() + k, xs[i]) - endValLengthL.begin();
        endValLengthL[l] = xs[i];
        endIdxLengthL[l] = i;
        if (l == k) k++;
    }

    return k;
}

// Lambda syntax to produce normal ascending sort order.
sort(liz.begin(), liz.end(), [v](point a, point b) {
	return a < b;
});
