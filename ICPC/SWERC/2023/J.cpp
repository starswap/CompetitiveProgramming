#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, P;
    cin >> N >> P;
    vector<int> cnts(N, 0);
    for (int n = 0; n < N - 1; ++n) {
        int a, b;
        cin >> a >> b;
        cnts[a]++;
        cnts[b]++;
    }    
    int c = 0;
    for (int n = 0; n < N; ++n) {
        if (cnts[n] == 1) c++;
    }
    int low = P / c;
    int numHi = P % c;
    cout << 2 * low + min(2, numHi) << endl;
    return 0;
}