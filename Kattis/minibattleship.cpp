#include <bits/stdc++.h>
using namespace std;

typedef complex<double> C;
typedef vector<double> vd;
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

enum State {
    UNKNOWN,
    MISS,
    HIT,
    SHIP,
};

int N, K;

vector<vector<State>> board;
vector<int> boats;

int next_r(int r, int c) {
    return (c == N - 1) ? r + 1 : r;
}

int next_c(int r, int c) {
    return (c == N - 1) ? 0 : c + 1;
}

int place_boats(int r, int c, int boats_available) {
    if (boats_available == 0) {
        if (r == N) return 1;
        else if (board[r][c] == HIT) return 0;
        else return place_boats(next_r(r, c), next_c(r, c), boats_available);
    }
    else if (r == N) return 0; // got to the end without placing all the boats
    else {

        int ans = 0;
        if (board[r][c] != HIT) ans += place_boats(next_r(r, c), next_c(r, c), boats_available); // skip this cell
        
        for (int b = 0; b < K; ++b) { // choose a boat to place
            if (!((1 << b) & boats_available)) continue; // used
            
            if (N - c >= boats[b]) { // space to the right
                bool can_place = true;
                rep(i, 0, boats[b]) {
                    can_place &= board[r][c + i] == UNKNOWN ||  board[r][c + i] == HIT;  // any misses = no place
                }
                vector<State> old(boats[b]);
                if (can_place) {
                    rep(i, 0, boats[b]) {
                        old[i] = board[r][c + i];
                        board[r][c + i] = SHIP;
                    }
                    ans += place_boats(next_r(r, c + boats[b] - 1), next_c(r, c + boats[b] - 1), boats_available ^ (1 << b));
                    rep(i, 0, boats[b]) {
                        board[r][c + i] = old[i];
                    }
                }
            }

            if (N - r >= boats[b] && boats[b] != 1) { // space to the right; only place size 1 one way
                bool can_place = true;
                rep(i, 0, boats[b]) {
                    can_place &= board[r + i][c] == UNKNOWN || board[r + i][c] == HIT;  // any misses = no place
                }
                vector<State> old(boats[b]);
                if (can_place) {
                    rep(i, 0, boats[b]) {
                        old[i] = board[r + i][c];
                        board[r + i][c] = SHIP;
                    }
                    ans += place_boats(next_r(r, c), next_c(r, c), boats_available ^ (1 << b));
                    rep(i, 0, boats[b]) {
                        board[r + i][c] = old[i];
                    }
                }
            }
        }
        return ans;
    }
}

int main() {
    cin >> N; cin >> K;
    board.assign(N, vector<State>(N, UNKNOWN));
    rep(i, 0, N) {
        string s; cin >> s;
        rep(j, 0, N) {
            if (s[j] == 'O') {
                board[i][j] = HIT;
            } else if (s[j] == 'X') {
                board[i][j] = MISS;
            }
        }
    }
    boats.assign(K, 0);
    rep(i, 0, K) {
        cin >> boats[i];
    }
    cout << place_boats(0, 0, (1 << K) - 1) << endl;   
}
