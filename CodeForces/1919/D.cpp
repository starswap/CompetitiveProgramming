#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// only 1 0
int N;
vector<int> as;
// look at answer
 
bool try_delete(std::map<int, int>::iterator it, map<int, int>& m) {
    
    int value = it->second;
    bool ok = ((next(it) != m.end() && (next(it)->second == value || next(it)->second == value - 1)) 
              || (it != m.begin() && (prev(it)->second == value || prev(it)->second == value - 1)))
              || (next(it) == m.end() && it == m.begin() && it->second == 0);
    if (ok) {
        m.erase(it);
    }
    return ok;
}

bool solve() {
    map<int, vector<std::map<int, int>::iterator>> mapA;
    map<int, int> mapB;
    for (int i = 0; i < N; ++i) {
        mapB[i] = as[i];
        mapA[as[i]].push_back(mapB.find(i));
    }

    while (mapB.size() >= 1) {
        auto [maxi, indxs] = *mapA.rbegin();
        for (std::map<int, int>::iterator i : indxs) {
            if (!try_delete(i, mapB)) {
                return false;
            }
        }
        mapA.erase(prev(mapA.end()));
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        as.assign(N, 0);
        int zeros = 0;
        for (int i = 0; i < N; ++i) {
            cin >> as[i];
            zeros += (as[i] == 0);
        }
        cout << (zeros == 1 && solve() ? "YES" : "NO") << endl;
    }
    return 0;
}

// map from number to indices of that number
// put the numbers in a map from index to number
// max number in map A
// test using map B
// delete from map A
// delete from map B