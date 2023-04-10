#include <bits/stdc++.h>
using namespace std;

struct point {
    double x, y;
    point():x(0),y(0) {}
};

const double PI = 3.14159265358979;

double rem(double x, double y) {
    if (x >= 0) {
        for (; x >= 0; x -= y) {}
        return x + y;
    }
    else {
        for (; x <= 0; x += y) {}
        return -(x - y);
    }
}

int main() {
    int N;
    cin >> N;
    vector<point> pts(N);
    for (int n = 0; n < N; ++n) {
        cin >> pts[n].x >> pts[n].y;
    }


    int bestK = 0;
    double bestScore = 0;
    for (int k = 3; k <= 8; ++k) {
        double minA = 1e20;
        double maxA = 0;
        double theta =  2 * PI / k;
        for (auto pt : pts) {
            double angle = atan2(pt.y, pt.x);
            double phi = rem(angle, theta);
            double q = PI - phi - (PI / 2 - theta / 2);
            double d = hypotl(pt.x, pt.y);
            double A = sin(q) * d / sin(theta / 2);
            minA = min(minA, A);
            maxA = max(maxA, A);
        }

        double outerArea = 0.5 * maxA * maxA * sin(theta); 
        double innerArea = 0.5 * minA * minA * sin(theta); 
        double score = innerArea / outerArea;

        if (score > bestScore) {
            bestScore = score;
            bestK = k;
        }
    }

    cout << fixed << setprecision(10);
    cout << bestK << " " << bestScore << endl;

    return 0;
}