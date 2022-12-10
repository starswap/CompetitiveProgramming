#include <bits/stdc++.h>
using namespace std;


const int MOD = 100000000;

inline int toAtom(int day, int val) {
    return day*MOD + (abs(val)*2 + (val < 0));
}
inline int notP(int hash) {
    if (hash % 2 == 0)
        return hash + 1;
    else
        return hash - 1;
}

unordered_map<int, vector<int>> AL;
unordered_map<int, vector<int>> AL_T;

inline void implies(int v1, int v2) {
    AL[v1].push_back(v2);
    AL_T[v2].push_back(v1);
}

set<int> visited;
vector<int> postOrder;
vector<set<int>> SCCs;

void dfs(int u, bool step2) {
    if (visited.contains(u)) return; // ok, no failure
    visited.insert(u);
    for (int v : ((step2) ? AL_T[u] : AL[u]) ) {
        dfs(v, step2);
    }
    if (!step2)
        postOrder.push_back(u);
    else
        SCCs.rbegin()->insert(u);
}

bool satFail() {
    postOrder.clear();
    visited.clear();
    for (auto &[u,vs] : AL) {
        dfs(u, false);
    }
    visited.clear();
    reverse(postOrder.begin(),postOrder.end());
    for (int u : postOrder) {
        SCCs.push_back(set<int>());
        dfs(u,true);
        for (int v : *SCCs.rbegin()) {
            if (SCCs.rbegin()->contains(notP(v))) {
                // cout << v << endl;
                return true;
            }   
        }
    }
    return false;
}

void printAL() {
    cout << AL.size() << endl;
    for (auto &[u,vs] : AL) {
        cout << u << endl;
    }
    for (auto &[u,vs] : AL) {
        for (auto v : vs) {
            cout << u << " " << v << endl;
        }
    }
}



int main() {
    int n;
    cin >> n;
    
    vector<int> d(7,0);
    vector<vector<int>> nb(n, vector<int>(7,0));

    AL.reserve(20*n); // should be enough

    // implies(0,1);
    // implies(1,3);
    // implies(3,4);
    // implies(4,5);
    // implies(5,7);
    // implies(7,6);
    // implies(6,4);
    // implies(3,2);
    // implies(2,1);

    // satFail();

    for (int i=0;i<7;++i) {
        cin >> d[i];
    } 
    for (int i=0;i<n;++i) {
        for (int j=0;j<7;++j) {
            cin >> nb[i][j];
        }
    }

    int AlSat, AlSun;
    cin >> AlSat;
    cin >> AlSun; 
    
    implies(toAtom(5,-1*AlSat),toAtom(5,AlSat));
    implies(toAtom(6,-1*AlSun),toAtom(6,AlSun));

    for (int k=0;k<n;++k) {
        for (int i=0;i<7;++i) {
            for (int j=i+1;j<7;++j) {
                int pi = nb[k][i];
                int pj = nb[k][j];
                // we require ¬p v ¬q so p -> ¬q
                implies(toAtom(i,pi),toAtom(j,-1*pj));
                implies(toAtom(j,pj),toAtom(i,-1*pi));
            }
        }
    }

    // printAL();

    cout << ((satFail()) ? "impossible" : "possible") << endl;

    return 0;
}