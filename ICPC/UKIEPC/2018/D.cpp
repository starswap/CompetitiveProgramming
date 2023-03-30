#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14159265358979323;
const double EPS = 1e-7;

inline double fpmod(double d, double m) {
    while (d < -EPS) {
        d += m;
    }
    while (d > m - EPS) {
        d -= m;
    }
    return d;
}

inline double amod(double d) { // angle mod
    return fpmod(d, 2 * PI);
}

inline double degtorad(double deg) { 
    return deg / 360.0 * 2 * PI;
};

double com(double theta, double scos, double ssin) {
    return (cos(theta) * ssin + sin(theta) * scos);
}

struct bucket {
    double dt, e, f;
    bucket(double dt, double e, double f): dt(dt), e(e), f(f) {}
};

int N;
vector<bucket> buckets;
vector<double> dt, e, f;

// Pre: Buckets already angle sorted; at least one empty bucket; at least one full bucket.
// Let 0 degrees be the top, and the angle increases clockwise.
double solve() {
    // Setup; initial O(N) processing
    double scos = 0;   // sum over all buckets of cos(d_i) * m_i
    double ssin = 0;   // sum over all buckets of sin(d_i) * m_i

    int lastfull = -1;      // index of last full bucket
    int lastempty = N - 1;  // index of last empty bucket

    for (int i = 0; i < N; ++i) {
        double m; // initial mass of current bucket
        if (dt[i] > PI - EPS) { // left half
            m = e[i]; // empty bucket
            lastfull = (lastfull == -1) ? ((i - 1) + N) % N : lastfull; // save lastfull / firstempty boundary
        } else {
            m = f[i];
        }
        scos += m * cos(dt[i]);
        ssin += m * sin(dt[i]);
    }

    cout << scos << endl;
    cout << ssin << endl;

    // Main algorithm to iterate over the data and find the optima; O(N log N)
    double ans = 0;
    double lasttheta = 0; // amount we have turned the wheel by so far
    int passedTop = 0; // number of buckets that have passed the top of the wheel

    while (passedTop < N)  { // stop once all buckets passed the top
        // Calculate how far we can turn now
        double angleTurnToNextEmpty = amod(PI - dt[lastfull]);
        double angleTurnToNextFull = amod(2 * PI - dt[lastempty]);
        double thetalow = lasttheta;
        double thetahigh = min(angleTurnToNextEmpty, angleTurnToNextFull);
        lasttheta = thetahigh; // save for next iteration of the outer while loop.

        // Ternary Search; since it's a sum of cosines and sines, it's unimodal
        while (thetahigh - thetalow > EPS) {
            double l = thetalow + (thetahigh - thetalow) / 3;
            double h = thetalow + 2 * (thetahigh - thetalow) / 3;
            if (com(l, scos, ssin) > com(h, scos, ssin)) { // discard right
                thetahigh = h;
            } else { // discard left
                thetalow = l;
            }
        }

        // Maximum c.o.m x value occurs somewhere between thetahigh and thetalow
        //   we don't care where.
        ans = max(ans, com((thetahigh + thetalow) / 2, scos, ssin));

        // When we turn the wheel to (thetahigh + thetalow) / 2 degrees
        //   we will move the lastfull to become empty.
        if (angleTurnToNextEmpty < angleTurnToNextFull + EPS) {
            // Remove old full mass
            scos -= f[lastfull] * cos(dt[lastfull]);
            ssin -= f[lastfull] * sin(dt[lastfull]);

            // Add new empty mass
            scos += e[lastfull] * cos(dt[lastfull]);
            ssin += e[lastfull] * sin(dt[lastfull]);

            lastfull--;
            lastfull = (lastfull + N) % N;
            passedTop++; // so we can exit on time
        }

        // When we turn the wheel to (thetahigh + thetalow) / 2 degrees
        //   we will move the lastempty to become full. (Possible that this and the previous one occurs)
        if (angleTurnToNextEmpty > angleTurnToNextFull - EPS) { 
            // Remove old full mass
            scos -= e[lastempty] * cos(dt[lastempty]);
            ssin -= e[lastempty] * sin(dt[lastempty]);

            // Add new empty mass
            scos += f[lastempty] * cos(dt[lastempty]);
            ssin += f[lastempty] * sin(dt[lastempty]);

            lastempty--;
            lastempty = (lastempty + N) % N;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    for (int i = 0; i < N; ++i) {
        double d, ea, fa;
        cin >> d >> ea >> fa;
        buckets.push_back(bucket(degtorad(d), ea, fa));
    }
    
    // Sentinel Buckets to ensure we never encounter a situation with 0 empty
    //   or 0 full buckets.
    N += 4;
    buckets.push_back(bucket(2 * EPS, 0.0, 0.0));
    buckets.push_back(bucket(PI - 2 * EPS, 0.0, 0.0));
    buckets.push_back(bucket(PI + 2 * EPS, 0.0, 0.0));
    buckets.push_back(bucket(2 * PI - 2 * EPS, 0.0, 0.0));
    
    // Angle sort (makes adding sentinels easier than relying on Robin's sort)
    sort(buckets.begin(), buckets.end(), [] (bucket a, bucket b) {return a.dt < b.dt;});

    // separate buckets to make access easier in solve();
    for (auto &[td, te, tf] : buckets) {
        dt.push_back(td);
        e.push_back(te);
        f.push_back(tf);
    } 

    cout << fixed << setprecision(10) << solve() << endl;
    return 0;
}
