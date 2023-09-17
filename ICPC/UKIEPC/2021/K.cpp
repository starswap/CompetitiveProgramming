#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

int main() {
    double n, m; 
    double l;
    cin >> n >> m >> l;

    double x = 0;
    double y = 0;
    
    double dx = 1;

    vector<pair<double, double>> points;
    bool across = false;
    while (true) {
        points.emplace_back(x ,y);
        if (hypot(x - n, y - m) == l) {break;}
        double nx = x, ny = y, nl = 0;
        if (across) {
            nx = x + dx;
            nl = l - dx;
        } else {
            ny = (y == 0) ? m : 0;
            nl = l - m;
        }
        across = !across;
        if (hypot(nx - n, ny - m) > nl + EPS) {
            if (y == 0) {
                y = (- l * l + m * m + (n - x) * (n - x))/(2 * m - 2 * l);
            } else {
                y = m - (((n - x) * (n - x) - l * l) / (-2 * l));
            }
            points.emplace_back(x ,y);
            break;
        } else {
            l = nl;
            x = nx;
            y = ny;
        }
    }
    points.emplace_back(n, m);

    cout << points.size() << endl;
    for (auto &[x, y] : points) {
        cout << x << " " << y << endl;
    }
    
    return 0;
}