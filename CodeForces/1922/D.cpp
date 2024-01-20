#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct monster {
    int attack;
    int defence;
    monster(int a, int d):attack(a), defence(d) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        list<monster> ms;
        for (int n = 0; n < N; ++n) {
            int A; cin >> A;
            ms.push_back(monster(A, 0));
        }
        for (auto &m : ms) {
            cin >> m.defence;
        }

        deque<list<monster>::iterator> q;
        for (auto it = ms.begin(); it != ms.end(); ++it) {
            q.push_back(it);
        }

        int total_dead = 0;
        for (int n = 0; n < N; ++n) {
            int dies = 0;
            deque<list<monster>::iterator> next_q;
            list<monster>::iterator last_t;
            bool waiting = false;
            while (!q.empty()) {
                auto it = q.front(); q.pop_front();
                auto n = next(it);
                auto p = prev(it);
                int damage = ((it == ms.begin()) ? 0 : p->attack) + (it == prev(ms.end()) ? 0 : n->attack);
                assert(damage >= 0);
                if (damage > it->defence) {
                    if (waiting) {
                        if (next(last_t) != it) {
                            next_q.push_back(next(last_t));
                        }
                    }

                    if (it != ms.begin()) {
                        if (!waiting || p != last_t) {
                            if (next_q.empty() || next_q.back() != p) {
                                next_q.push_back(p);
                            }
                        }
                    }

                    if (waiting) {
                        ms.erase(last_t);
                    }
                    last_t = it;
                    waiting = true;
                    dies++;
                } else {
                    if (waiting) {
                        if (last_t != prev(ms.end())) {next_q.push_back(next(last_t));}                            
                        ms.erase(last_t);
                        waiting = false;
                    }
                }
            }
            if (waiting) {
                if (last_t != prev(ms.end())) {next_q.push_back(next(last_t));}                            
                ms.erase(last_t);
                waiting = false;
            }
            while (!next_q.empty()) {
                q.push_back(next_q.front());
                next_q.pop_front();
            }
            cout << dies << " ";
            total_dead += dies;
        }
        cout << endl;
        assert(total_dead <= N);
    }
    return 0;
}