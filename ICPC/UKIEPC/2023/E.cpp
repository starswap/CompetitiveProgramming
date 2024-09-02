#include <bits/stdc++.h>
using namespace std;

/* Doing multiple repeats and trying each length separately 
   (rather than allowing additions and removals)
   made the difference. Also had to tune the parameters a bit. 
   Eventually you get lucky. */

const int MAX_N = 30;
const double T_MAX = 1000;
const double T_MIN = 0;
const double EPOCHS = 10000;
const double DELTA_T = (T_MAX - T_MIN) / EPOCHS;
const int NUM_TRIES = 10;

int N;
set<int> in;
int D[MAX_N][MAX_N];
string s;

double rand_dec() {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

tuple<int, int, int> do_swap() {
    int to_add = rand() % N;
    while (in.count(to_add)) to_add = rand() % N;

    int to_remove = rand() % N;
    while (!in.count(to_remove)) to_remove = rand() % N;

    int dE = D[to_add][to_add];
    for (int i : in) dE += D[i][to_add];
    for (int i : in) dE -= D[i][to_remove];
    dE -= D[to_add][to_remove];

    return make_tuple(to_add, to_remove, dE);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    srand(time(0));

    cin >> s;
    N = s.size();

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            cin >> D[i][j];
            D[j][i] = D[i][j];
        }
    }

    int best_E = 0;
    vector<int> best_in;
    for (int tr = 0; tr < NUM_TRIES; ++tr) {
        for (int l = 1; l < N; ++l) {
            in.clear();
            int E = 0;

            for (int i = 0; i < l; ++i) {
                int to_add = rand() % N;
                while (in.count(to_add)) to_add = rand() % N;
                in.insert(to_add);
            }

            /* Calculate score */
            for (int i : in) {
                for (int j : in) {
                    if (i > j) continue;
                    E += D[i][j];
                }
            }
            
            /* Simulated Annealing */
            for (double t = T_MAX; t > T_MIN; t -= DELTA_T) {
                auto [to_add, to_remove, dE] = do_swap();
                if (dE >= 0 || (exp(dE / t) > rand_dec())) {
                    in.erase(to_remove);
                    in.insert(to_add);
                    E += dE;
                }
            }

            if (E > best_E) {
                best_E = E;
                best_in = vector<int>{in.begin(), in.end()};
            }

        }
        
    }

    /* Try with all letters (only 1 full subset) */
    int E = 0;
    for (int i = 0 ; i < N; ++i) {
        for (int j = i ; j < N; ++j) {
            E += D[i][j];
        }
    }
    if (E > best_E) {
        best_E = E;
        best_in.clear();
        for (int i = 0; i < N; ++i) {
            best_in.push_back(i);
        }
    }


    /* Output results */
    cout << best_in.size() << endl;
    if (best_in.size() > 0) {
        for (int c : best_in) {
            cout << s[c];
        }
        cout << endl;
    }

    return 0;
}

