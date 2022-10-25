#include <bits/stdc++.h>
using namespace std;

const int MAX_DEPTH = 10000;
int R,C;
vector<string> grid(R); 

int dr[] = {1,0,0,-1};
int dc[] = {0,1,-1,0};

const int INF = 100000000;

vector<vector<bool>> visited;
vector<vector<int>> minCost;

int dijkstra(int r, int c) {
    visited.assign(R,vector<bool>(C,false));

    priority_queue< 
        pair<int,pair<int,int>>,
        vector<pair<int,pair<int,int>>>,
        greater<pair<int,pair<int,int>>>> q;

    minCost.assign(R,vector<int>(C,INF));
    q.push(make_pair(0,make_pair(r,c)));
    minCost[r][c] = 0;

    while (!q.empty()) {
        auto [dist,coords] = q.top(); q.pop();
        auto [r,c] = coords;
        
        if (dist != minCost[r][c]) {continue;}

        visited[r][c] = true;

        if (grid[r][c] == 'D' && (r == 0 || c == 0 || r == (R-1) || c == (C-1))) {
            return dist;
        }
        else {
            for (int i=0;i<4;++i) {
                int resR = dr[i]+r;
                int resC = dc[i]+c;
                
                if (resR >= R || resR < 0 || resC >= C || resC < 0) {continue;}
                if (grid[resR][resC] == '#') {continue;};
                if (visited[resR][resC]){continue;};

                int newDist;
                if (grid[r][c] == 'D') {newDist = dist;} else {newDist = dist+1;};
                
                if (newDist < minCost[resR][resC]) {
                    minCost[resR][resC] = newDist;
                    q.push(make_pair(newDist,make_pair(resR,resC)));
                }
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &R,&C);
    grid.assign(R,"");
    for (int r=0;r<R;++r) {
        cin >> grid[r];
    }
    int tr,tc;
    scanf("%d %d",&tr,&tc);
    tr--;
    tc--;
    printf("%d\n", dijkstra(tr,tc));
    return 0;
}

