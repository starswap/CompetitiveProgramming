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


double solve(vector<point> &pts) {
    vector<point> H = CH(pts);
    int n = H.size();
    double miniMax = INF;
    for (int i = 0; i < n - 1; ++i) {
        double maxi = -1;
        for (point p : H) {
            maxi = max(maxi, ptToLine(p,line(H[i], H[i+1])));  
        }
        miniMax = min(maxi, miniMax);
    }
    return miniMax;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N;
    cin >> N;

    vector<point> pts(N);
    for (int n = 0; n < N; ++n) {
        double x, y;
        cin >> x >> y;
        pts[n] = point(x, y); 
    }

    cout << solve(pts) << endl;

    return 0;
}