#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    set<int> cands;
    for (int i = 2; i < N; ++i) {cands.insert(i);}

    auto it = cands.begin();
    while (!(it == cands.end())) {
        int i = *it;
        if (N % i != 0) {
            cout << i << endl;
            break;
        } else {
            vector<int> to_remove;
            for (int c : cands) {
                if (c % i == 0) {to_remove.push_back(c);}
            }
            for (int c : to_remove) {
                cands.erase(c);
            }
        }
        it = cands.upper_bound(i);
    }

    return 0;
}