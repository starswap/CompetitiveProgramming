#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

double fceil(double f) {
    if (fabs(f - round(f)) < EPS) { // By empirical verification this is actually necessary.
        return round(f);
    } else {
        return ceil(f);
    }
}

int main() {
    double H1, D1, T1; cin >> H1 >> D1 >> T1;
    double H2, D2, T2; cin >> H2 >> D2 >> T2;

    int p1_dead_at = fceil(H1 / D2) * T2 - T2;
    int p2_dead_at = fceil(H2 / D1) * T1 - T1;

    if (p1_dead_at == p2_dead_at) {
        cout << "draw" << endl;
    } else if (p1_dead_at >  p2_dead_at) {
        cout << "player one" << endl;
    } else {
        cout << "player two" << endl;
    }

    return 0;
}