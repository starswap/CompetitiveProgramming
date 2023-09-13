#include <bits/stdc++.h>
using namespace std;

const int UNK = 256;
const int INF = 100000;
vector<tuple<int, int, int>> target_state(256, make_tuple(UNK, UNK, UNK));
int cost[257][257][257];
tuple<int, int, int> parent[257][257][257];
string operation[257][257][257];

tuple<int, int, int> pushX(int X, int Y, int S) {return make_tuple(X, Y, X);}
tuple<int, int, int> pushY(int X, int Y, int S) {return make_tuple(X, Y, Y);}
tuple<int, int, int> popX(int X, int Y, int S) {return make_tuple(S, Y, UNK);}
tuple<int, int, int> popY(int X, int Y, int S) {return make_tuple(X, S, UNK);}
tuple<int, int, int> addX(int X, int Y, int S) {return make_tuple(X, Y, S == UNK || X == UNK ? UNK : (S + X) & ((1 << 8) - 1));}
tuple<int, int, int> addY(int X, int Y, int S) {return make_tuple(X, Y, S == UNK || Y == UNK ? UNK : (S + Y) & ((1 << 8) - 1));}
tuple<int, int, int> zeroX(int X, int Y, int S) {return make_tuple(0, Y, S);}
tuple<int, int, int> zeroY(int X, int Y, int S) {return make_tuple(X, 0, S);}
tuple<int, int, int> oneX(int X, int Y, int S) {return make_tuple(1, Y, S);}
tuple<int, int, int> oneY(int X, int Y, int S) {return make_tuple(X, 1, S);}

tuple<typeof &pushX, string, int> instructions[] = {
    make_tuple(popX, "PL X", 1),
    make_tuple(zeroX, "ZE X", 1),
    make_tuple(zeroY, "ZE Y", 1),
    make_tuple(oneX, "ST X", 1),
    make_tuple(oneY, "ST Y", 1),
    make_tuple(pushX, "PH X", 1),
    make_tuple(pushY, "PH Y", 1),
    make_tuple(popY, "PL Y", 1),
    make_tuple(addX, "PH X\nAD", 2),
    make_tuple(addY, "PH Y\nAD", 2),
};

void dijkstra(int N) {
    priority_queue<pair<int, tuple<int, int, int>>> pq;

    for (int i = 0; i <= 256; ++i) {
        for (int j = 0; j <= 256; ++j) {
            for (int k = 0; k <= 256; ++k) {
                cost[i][j][k] = INF;
            }
        }
    }

    cost[UNK][UNK][UNK] = 0;
    pq.emplace(-cost[UNK][UNK][UNK], make_tuple(UNK, UNK, UNK));
    while (pq.size() > 0) {
        auto [dist, state] = pq.top(); pq.pop();
        auto [x, y, s] = state;
        dist = -dist;
        if (cost[x][y][s] != dist) continue;
        if (x != UNK && target_state[x] == make_tuple(UNK, UNK, UNK)) target_state[x] = make_tuple(x, y, s);
        if (x == N) break;
        
        for (auto &[fn, instr, cnt] : instructions) {
            auto [newX, newY, newS] = fn(x, y, s);
            if (dist + cnt < cost[newX][newY][newS]) {
                cost[newX][newY][newS] = dist + cnt;
                pq.emplace(-cost[newX][newY][newS], make_tuple(newX, newY, newS));
                parent[newX][newY][newS] = make_tuple(x, y, s);
                operation[newX][newY][newS] = instr;
            }
        }
    }
}

void do_output(int N) {
    auto [x, y, s] = target_state[N];
    vector<string> operations;
    while (!(x == UNK && y == UNK && s == UNK)) {
        operations.push_back(operation[x][y][s]);
        tuple<int, int, int> state = parent[x][y][s]; 
        x = get<0>(state);
        y = get<1>(state);
        s = get<2>(state);
    }
    reverse(operations.begin(), operations.end());
    for (string s : operations) {
        cout << s << endl;
    }
    cout << "DI X" << endl; 
}

int main() {
    int N; cin >> N;
    dijkstra(N);
    do_output(N);
    return 0;
}