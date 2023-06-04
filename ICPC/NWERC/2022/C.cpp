#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

 long long squares(double r) {
    long long quadrant = 0;
    for (int x = 1.0; x <= r; ++x) {
        double y = sqrt(r * r - x * x);
        quadrant += floor(y);
    }
    return 4 * quadrant;
}

int main() {
    int target;
    cin >> target;

    double lo = 0;
    double hi  = 1e5;

    while (hi - lo > EPS) {
        double m = (hi + lo) / 2.0;
        if (squares(m) <= target) {
            lo = m;
        } else {
            hi = m;
        }
    }
    cout << fixed << setprecision(10) << hi << endl;

    return 0;
}
