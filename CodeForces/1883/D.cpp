#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    multiset<int> begins;
    multiset<int> ends;
    int N = 0;
    while (T--) {
        char c;
        int l, r;
        cin >> c >> l >> r;
        
        if (c == '+') {
            begins.insert(l);
            ends.insert(r);
            N++;
        } else {
            begins.erase(begins.find(l));
            ends.erase(ends.find(r));
            N--;
        }

        if (N > 0 && *ends.begin() < *begins.rbegin()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}