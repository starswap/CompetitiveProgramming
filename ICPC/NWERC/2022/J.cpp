#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> convincingness(N, 0);
    vector<tuple<int, int, int>> windows;
    
    for (int n = 0; n < N; ++n) {
        int s, e;
        cin >> s >> e;
        windows.emplace_back(s, e, n);
    }

    sort(windows.begin(), windows.end(), [] (tuple<int, int, int> p1, tuple<int, int, int> p2) { 
        return get<1>(p2) - get<0>(p2) > get<1>(p1) - get<0>(p1);
    });

    set<int> starts;
    set<int> ends;

    for (auto &[s, e, n] : windows) {
        int start_before_or_equal = starts.upper_bound(s) - starts.begin();
        int end_before = ends.lower_bound(e) - ends.begin();
        int end_after_or_equal = ends.size() - end_before;
        
    }
    
    return 0;
}