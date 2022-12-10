#include <bits/stdc++.h>
using namespace std;

const int UNSEEN = 0;
const int EXPLORING = 1;
const int FINISHED = 2;

int N,M;
long long K;
vector<vector<int>> AL;
vector<int> A;

// unordered_set<int> visited;
vector<int> visitedStateThisTime;
bool containsCycle(int req, int i) {
    if (A[i] > req) return false;
    if (visitedStateThisTime[i] == EXPLORING) return true;
    if (visitedStateThisTime[i] == FINISHED) return false; // ?

    visitedStateThisTime[i] = EXPLORING;

    bool foundCycle = false;
    for (int v : AL[i]) {
        foundCycle |= containsCycle(req, v); 
    }
    visitedStateThisTime[i] = FINISHED;

    return foundCycle;
}
    
vector<int> dpPathLength;

int doDP(int req, int u) {
    if (dpPathLength[u] != -1) return dpPathLength[u];
    else {
        int best = 0;
        for (int v : AL[u]) {
            if (A[v] > req) continue;
            else {
                best = max(best, doDP(req, v));
            }
        }
        best++;
        dpPathLength[u] = best;
        return best;
    }
}

int treeDiam(int req) {
    dpPathLength.assign(N,-1);

    int best = -1;

    for (int i=0;i<N;++i) {
        if (A[i] > req) continue;
        best = max(best,doDP(req, i));
    }
    return best;
}


bool can(int req) {
    visitedStateThisTime.assign(N, UNSEEN);
    
    for (int i=0;i<N;++i) {
        if (!visitedStateThisTime[i]) { // visited.contains
            if (containsCycle(req,i)) return true;
        }
    }
    int maxLength = treeDiam(req);
    return maxLength >= K; 
}


int main() {
    cin >> N >> M >> K;

    A.assign(N,0);
    AL.assign(N,vector<int>());
    
    for (int n=0;n<N;++n) {
        cin >> A[n];    
    }
    for (int m=0;m<M;++m) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        AL[x].push_back(y);
    }


    int L = 0;
    int R = *max_element(A.begin(),A.end());

    while (L < R) {
        int M = (L+R)/2;
        if (can(M)) {
            R = M;
        }
        else {
            L = M + 1;
        }
    }
    if (L == R && can(L)) cout << L;
    else cout << -1;

    return 0;
}