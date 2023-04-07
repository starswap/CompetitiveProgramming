#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14159265358979323;
const double sq = 5;
const double ro = 2.5 * PI;
const bool CIRCLE = false;
const bool SQUARE = true;
const double INF = 1e10;

vector<vector<bool>> grid; // true <=> square
vector<vector<double>> dp;


int main() {
    int R, C;
    cin >> R >> C;
    
    grid.assign(R, vector<bool>(C, false));

    for (int r = 0; r < R; ++r) {
        string row;
        cin >> row;

        for (int c=0;c<C;++c) {
            grid[r][c] = row[c] == 'X';
        }
    }


    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> q;
    vector<vector<double>> cost;
    vector<vector<vector<pair<double, pair<int,int>>>>> AL;

    AL.assign(2 * R + 1, vector<vector<pair<double, pair<int, int>>>>(2 * C + 1, vector<pair<double, pair<int, int>>>()));
    cost.assign(2 * R + 1, vector<double>(2 * C + 1, INF));

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {

            // Since the DP works we know we can actually skip the reverse edges and the extra two circle edges that won't ever be needed, but if you wanted to you could add those in.
        
            AL[2 * r][2 * c].emplace_back(sq, make_pair(2 * r + 1, 2 * c));
            AL[2 * r][2 * c].emplace_back(sq, make_pair(2 * r, 2 * c + 1));
            AL[2 * r][2 * c + 1].emplace_back(sq, make_pair(2 * r, 2 * c + 2));
            AL[2 * r][2 * c + 2].emplace_back(sq, make_pair(2 * r + 1, 2 * c + 2));
            AL[2 * r + 1][2 * c].emplace_back(sq, make_pair(2 * r + 2, 2 * c));
            AL[2 * r + 1][2 * c + 2].emplace_back(sq, make_pair(2 * r + 2, 2 * c + 2));
            AL[2 * r + 2][2 * c].emplace_back(sq, make_pair(2 * r + 2, 2 * c + 1));
            AL[2 * r + 2][2 * c + 1].emplace_back(sq, make_pair(2 * r + 2, 2 * c + 2));

            if (grid[r][c] == CIRCLE) {
                AL[2 * r][2 * c + 1].emplace_back(ro, make_pair(2 * r + 1, 2 * c + 2));
                AL[2 * r + 1][2 * c].emplace_back(ro, make_pair(2 * r + 2, 2 * c + 1));
                // AL[2 * r][2 * c + 1].emplace_back(ro, make_pair(2 * r + 1, 2 * c));
                // AL[2 * r + 1][2 * c + 2].emplace_back(ro, make_pair(2 * r + 2, 2 * c + 1));
            }
        }
    }

    cost[0][0] = 0;
    q.emplace(0, make_pair(0, 0));

    while (q.top().second != make_pair(2*R, 2*C) && !q.empty()) {
        auto [cost_in_q, loc] = q.top(); q.pop();
        auto [r, c] = loc;
        // cout << "(" << r << "," << c << ")" << endl;
        if (cost_in_q != cost[r][c]) continue;
        else {
            for (pair<double, pair<int, int>> t : AL[r][c]) {
                auto [w, targ] = t;
                auto [rt, ct] = targ;
                if (cost_in_q + w < cost[rt][ct]) {
                    cost[rt][ct] = cost_in_q + w;
                    q.emplace(cost[rt][ct], make_pair(rt, ct));
                }
            }
        }
    }
 
    cout << fixed << setprecision(10) << cost[2 * R][2 * C] << endl;
    return 0;
}
