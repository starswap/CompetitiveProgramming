// Coded after looking at editorial.
// Points to learn:
//    - The cycle can be oriented CW or CCW - choose a way and try all others.
//    - Once the cycle is fixed, the rest is fully determined because we have trees coming off of the cycle.


#include <bits/stdc++.h>
using namespace std;
int N;

const int UNVISITED = 0;
const int EXPLORING = 1;
const int FINISHED  = 2;
const int NOT_FOUND = -1;
const int CYCLE_COMPLETED = -2;
const unordered_set<int> UNALLOC;

typedef int vertex;
typedef int houseNums;

vector<vector<pair<vertex,houseNums>>> AL;
vector<unordered_set<int>> allocs; // for each vertex, the non-one number allocated to it.
map<pair<int,int>,int> edgeAllocs;

vector<tuple<vertex,vertex,houseNums>> EL; // edges in order;


unordered_set<vertex> cycle; 
vector<int> vis;
int cycleFind(int u,int p) {
    if (vis[u] == FINISHED) {
        return NOT_FOUND;
    }
    else if (vis[u] == EXPLORING) {
        cycle.insert(u);
        return u;
    }
    else if (vis[u] == UNVISITED) {
        vis[u] = EXPLORING;
        for (auto &[v,h] : AL[u]) {
            if (v == p) continue;

            int cycleState = cycleFind(v,u);
            if (cycleState == u) {
                return CYCLE_COMPLETED;
            }
            else if (cycleState == CYCLE_COMPLETED) {
                return CYCLE_COMPLETED;
            }
            else if (cycleState != NOT_FOUND) {
                cycle.insert(u);
                return cycleState;
            }
        }
        return -1;
    } 
    else {
        cout << "ERROR" << endl;
        return -1;
    }
}


bool treeAlloc(int u, int p) {  
    for (auto [v,h] : AL[u]) {
        if (cycle.contains(v) || v == p) {continue;}

        if (allocs[u].contains(h))
            return false;
        else {
            allocs[u].insert(h);
            edgeAllocs.emplace(make_pair(min(u,v),max(u,v)),v);

        }
        treeAlloc(v,u);
    }
    return true;
}


bool cycleAlloc(int pref) {
    bool consistent = true;
    allocs.assign(N,UNALLOC);
    edgeAllocs.clear();
    vertex v = *cycle.begin();
    vertex prevV = -1;
    do {
        auto [u,h] = AL[v][pref];
        if (u != prevV) {
            allocs[v].insert(h);
            
            edgeAllocs.emplace(make_pair(min(u,v),max(u,v)),u);

            consistent &= treeAlloc(v,-1);
            prevV = v;
            v = u;
        }
        else {
            auto [u_prime,h_prime] = AL[v][1-pref];
            allocs[v].insert(h_prime);
            
            edgeAllocs.emplace(make_pair(min(u_prime,v),max(u_prime,v)),u_prime);

            consistent &= treeAlloc(v,-1);
            prevV = v;
            v = u_prime;
        }

    } while (v != *cycle.begin());
    return consistent;
}

int main() {
    scanf("%d",&N);
    AL.assign(N,vector<pair<vertex,houseNums>>());
    vis.assign(N,UNVISITED);
    cycle.clear();

    for (int i=0;i<N;++i) {
        int u,v,h;
        scanf("%d %d %d",&u,&v,&h);
        u--;
        v--;
        AL[u].emplace_back(v,h);
        AL[v].emplace_back(u,h);
        EL.emplace_back(u,v,h);
    }

    cycleFind(0,-1);

    if (!cycleAlloc(0) && !cycleAlloc(1) ) { //short circuiting
        cout << "impossible" << endl;
    }
    else {
        vector<vertex> ans;
        for (auto [u,v,h] : EL) {
            ans.push_back(edgeAllocs[make_pair(min(u,v),max(u,v))]);
        }
        int i;
        for (i=0;i<ans.size()-1;++i) {
            cout << ans[i]+1 << " ";
        }
        cout << ans[i]+1 << endl;
    }

    return 0;
}