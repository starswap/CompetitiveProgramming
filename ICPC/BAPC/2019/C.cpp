#include <bits/stdc++.h>
using namespace std;


const int DANGLING = -10;

int output[3] = {0, -1, -2};
int req[3] = {-1, -1, -1};
vector<pair<int, int>> splitters;

int solve(int size, int i, int& target) { // size = power of 2 for curr node; i = index for (ignore / c / d)
    if (size <= req[i]) {                 // need all of this node
        target = output[i];               // so send the previous node's output to the correct location
        req[i] -= size;                   // requirements have reduced now for that node
        if (req[i] > 0) return i;         // on the other side of the current tree do we need to carry on with this i
        else return i + 1;                // or move on to the next i?
    } else {                              // will need to subdivide this node
        int start = splitters.size();
        target = start;                   // pipe the output of the previous node into this one 
        
        // Build new 1:1 splitter
        splitters.emplace_back(start + 1, start + 2);
        splitters.emplace_back(start, DANGLING);      // will cover this dangling in the next recursive calls
        splitters.emplace_back(DANGLING, start);      // will cover this dangling in the next recursive calls

        int new_i = solve(size / 2, i, splitters[start + 1].second); // connect up the first dangler
        return solve(size / 2, new_i, splitters[start + 2].first);   // connect up the second dangler
    }
}

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int x = 1;
    while (x <= c + d) {
        x <<= 1;
    }

    req[0] = (x - c - d);
    req[1] = c;
    req[2] = d;

    int _ignore = 0;
    solve(x, 0, _ignore);
    cout << splitters.size() << endl;
    for (auto [i, j] : splitters) {
        cout << i << " " << j << endl;
    }
    return 0;
}