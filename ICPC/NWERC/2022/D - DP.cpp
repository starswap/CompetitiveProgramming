#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14159265358979323;
const double sq = 5;
const double ro = 2.5 * PI;
const bool CIRCLE = false;
const bool SQUARE = true;

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

    dp.assign(2*R + 1, vector<double>(2*C + 1, 0.0));
    for (int r = 2 * R ; r >= 0; --r) {
        for (int c = 2 * C; c >= 0; --c) {
            if (r == 2 * R || c == 2 *  C) {
                dp[r][c] = sq*((2 * R - r) + (2 * C - c));
            } else {
                if (r % 2 == 0 && c % 2 == 0) {
                    dp[r][c] = min(dp[r+1][c], dp[r][c+1]) + sq;
                } else {
                    if (c % 2 == 1) {
                        if (grid[r/2][c/2] == CIRCLE) {
                            dp[r][c] = min(dp[r+1][c+1] + ro, dp[r][c+1] + sq);
                        } else {
                            dp[r][c] = dp[r][c+1] + sq;
                        }
                    } else {
                        if (grid[r/2][c/2] == CIRCLE) {
                            dp[r][c] = min(dp[r+1][c+1] + ro, dp[r+1][c] + sq);
                        } else {
                            dp[r][c] = dp[r+1][c] + sq;
                        }
                    }
                }
	        }
        }
    }

    cout << fixed << setprecision(10) << dp[0][0] << endl;
    return 0;
}
