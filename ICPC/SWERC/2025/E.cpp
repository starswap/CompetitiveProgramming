#include <bits/stdc++.h>


#define int long long
#define MUTLITEST false

using namespace std;

int n, q;
const int MAX_N = 2 * 1e5 + 7;
int pre4[MAX_N];
int pre8[MAX_N];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> q;
    char c;
    
    for (int i = 1; i <= n; i++){
        cin >> c;
        if(c == '4') {
            pre4[i] = 1;
        }
        if(c == '8') {
            pre8[i] = 1;
        }

        pre4[i] += pre4[i - 1];
        pre8[i] += pre8[i - 1];
    }
    
    long long l, r, x, y;

    for (int i = 0; i < q; i++) {
        cin >> l >> r >> x >> y;


        long long no_of4 = pre4[r] - pre4[l - 1];
        long long no_of8 = pre8[r] - pre8[l - 1];

        x = abs(x);
        y = abs(y);
        
        if (x + y > no_of4 + 2 * no_of8) {
            cout << "NO\n";
            continue;
        }

        if (x > no_of4 + no_of8) {
            cout << "NO\n";
            continue;
        }

        if (y > no_of4 + no_of8) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
    }

    return 0;
}
