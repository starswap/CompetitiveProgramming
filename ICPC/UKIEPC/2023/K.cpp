#include <bits/stdc++.h>
using namespace std;

int N, M;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    vector<pair<int, int>> Es(M);
    int higher = 0;
    for (int m = 0; m < M; ++m) {
        cin >> Es[m].first >> Es[m].second;
        if (Es[m].first > Es[m].second) higher++;
    }

    int id = 1;
    vector<int> ids;
    for (auto [u, v] : Es) {
        if ((higher >= (M + 1) / 2 && u > v) || (higher < (M + 1) / 2 && u < v)) {
            ids.push_back(id);
        }
        id++;
    }

    cout << "YES" << endl;
    cout << ids.size() << endl;
    for (int i : ids) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
