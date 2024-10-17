#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = 3.14159265358979323846264338;
const double EPS = 1e-7;

struct point {
    ll x;
    ll y;
};

struct vec {
    ll x;
    ll y;
    vec(ll _x, ll _y): x(_x), y(_y) {}
};

vec toVec(const point& a, const point& b) {
    return vec(b.x - a.x, b.y - a.y);
}

ll dot(vec a, vec b) {
    return a.x * b.x + a.y * b.y;
}

ll cross(vec a, vec b) {
    return a.x * b.y - a.y * b.x;
}

ll norm_sq(vec v) {
    return v.x * v.x + v.y * v.y;
}

ll angle(const point &a, const point& o, const point& b) {
    vec oa = toVec(o, a), ob = toVec(o, b);
    return dot(oa, ob);
}

bool same_direction(vec a, vec b) {
    return cross(a, b) == 0;
}

int main() {
    point p, q, r, s;
    cin >> p.x >> p.y >> q.x >> q.y >> r.x >> r.y >> s.x >> s.y;
    bool four_rangle = !angle(p, q, r) && !angle(q, r, s) && !angle(r, s, p) && !angle(r, s, p);
    bool all_sides_equal = norm_sq(toVec(p, q)) == norm_sq(toVec(q, r))
                        && norm_sq(toVec(q, r)) == norm_sq(toVec(r, s))
                        && norm_sq(toVec(s, p)) == norm_sq(toVec(r, s));

    bool pqsr_parallel = same_direction(toVec(p, q), toVec(r, s));
    bool psqr_parallel = same_direction(toVec(p, s), toVec(q, r));
    bool kite = 
        ((norm_sq(toVec(p, s)) == norm_sq(toVec(s, r))) && (norm_sq(toVec(p, q)) == norm_sq(toVec(q, r))) && (angle(s, p, q) == angle(q, r, s))) || 
        ((norm_sq(toVec(q, p)) == norm_sq(toVec(s, p))) && (norm_sq(toVec(r, q)) == norm_sq(toVec(s, r))) && (angle(p, q, r) == angle(p, s, r)));

    if (four_rangle && all_sides_equal) {
        cout << "square" << endl;
    } else if (four_rangle) {
        cout << "rectangle" << endl;
    } else if (all_sides_equal) {
        cout << "rhombus" << endl;
    } else if (pqsr_parallel && psqr_parallel) {
        cout << "parallelogram" << endl;
    } else if (pqsr_parallel || psqr_parallel) {
        cout << "trapezium" << endl;
    } else if (kite) {
        cout << "kite" << endl;
    } else {
        cout << "none" << endl;
    }

    return 0;
}
