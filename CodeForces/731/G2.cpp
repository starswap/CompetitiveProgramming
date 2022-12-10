#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 400000;
const int INF = -1;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;

vector<vector<int>> AL;
vector<int> state;
set<int> canSee;
set<int> A;
set<int> B;
set<int> AA;
set<int> BB;
void dfs(int u, int mode) {
    canSee.insert(u);
    // cout << u << endl;
    if (mode == 0) { 
        if (state[u] == GREY) {A.insert(u); return;}
        if (state[u] == BLACK) {B.insert(u); return;}
    }
    else if (mode == 1) {
        if (AA.contains(u)) return;
        AA.insert(u);
    }
    else if (mode == 2) {
        if (BB.contains(u)) return;
        BB.insert(u);
    }   

    state[u] = GREY;
    for (int v : AL[u]) {
        dfs(v, mode);
    }
    state[u] = BLACK;
}

int main() {
    int T;
    cin >> T;
    for (int t=0;t<T;++t) {
        int N,M;
        cin >> N >> M;
        AL.assign(N,vector<int>());
        for (int m=0;m<M;++m) {
            int x,y;
            cin >> x >> y;
            x--; y--;
            AL[x].push_back(y);
        }
        state.assign(N,WHITE);
        AA.clear();
        A.clear();
        B.clear();
        BB.clear();
        canSee.clear();

        dfs(0,0);
        for (int a : A) {
            dfs(a,1);
        }
        for (int b : B) {
            dfs(b,2);
        }

        for (int i=0;i<N;++i) {
            if (AA.contains(i))
                cout << "-1";
            else if (BB.contains(i))
                cout << "2";
            else if (canSee.contains(i))
                cout << "1";
            else
                cout << "0";
            cout << " "; 
        }
        cout << endl;
    }

    return 0;
}