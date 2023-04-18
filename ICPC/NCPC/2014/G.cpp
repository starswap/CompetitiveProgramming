#include <bits/stdc++.h>
using namespace std;

enum state { UNVISITED, VISITED, LEFT }; 
int n, k;

vector<vector<int>> AL;
vector<state> states;
vector<int> cycles;
vector<int> components;

tuple<int, int, int> dfs(int x);

void getCycles() {
    for (int i = 0; i < n; ++i) {
        if (states[i] != LEFT) {
            auto [cycle, comp, node] = dfs(i);
            if (cycle != -1) {
                cycles.push_back(cycle);
                components.push_back(comp);
            }
        }
    }
}

// cycle size, component size, node looking for;
tuple<int, int, int> dfs(int x) {
    if (states[x] == VISITED) {
        return make_tuple(0, 0, x);
    } else {
        states[x] = VISITED;
        int currCycle = -1;
        int currComp = 0; 
        int finalNode = -1;

        for (int v : AL[x]) {
            auto [cycle, comp, nodeLookingFor] = dfs(v);
            if (cycle > currCycle) {
                currCycle = cycle;
                if (nodeLookingFor != -1) {
                    currCycle += 1;
                    if (nodeLookingFor != x) {
                       finalNode = nodeLookingFor; 
                    }
                }
            }
            currComp += comp;
        }
        states[x] = LEFT;
        return make_tuple(currCycle, currComp + 1, finalNode);
    }
}

int maxCan = 0;
vector<vector<int>> DP(1001, vector<int>(1001, -1));

bool doDP(int amntLeft, int compIdx) {
    if (amntLeft == 0) {
        return true;
    }
    else if (compIdx > components.size() - 1) {
        return false;
    }
    else if (DP[amntLeft][compIdx] != -1) {
        return DP[amntLeft][compIdx];
    } else {

        bool can = false;
        for (int i = cycles[compIdx]; i <= components[compIdx]; i++) {
            if (amntLeft - i >= 0) {
                can |= doDP(amntLeft - i, compIdx + 1);
            }
        }
        can |= doDP(amntLeft, compIdx + 1);

        if (can) {
            DP[amntLeft][compIdx] = 1;
        } else {
            DP[amntLeft][compIdx] = 0;
        }
        return DP[amntLeft][compIdx];
    }
}




int main() {
    cin >> n >> k;
    AL.assign(n, vector<int>());
    states.assign(n, UNVISITED);

    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        d--;
        AL[d].push_back(i);
    }
    
    getCycles();

    int i = k;
    while (doDP(i, 0) == 0) {
        i--;
    }
    cout << i << endl;

    return 0;
}