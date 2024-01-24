#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    int mini = 1000000000;
    while (T--) {
        int Y, p1, p2; cin >> Y >> p1 >> p2;
        mini = min(mini, Y +((p1 * p2) /  __gcd(p1, p2)));
    }
    cout << mini << endl;
    return 0;
}