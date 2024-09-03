#include <bits/stdc++.h>
using namespace std;

/*
    Using Robin's method from the slides.
    Namely, meet in the middle brute forcing.
*/

const int MAX_N = 30;
const int CURR = MAX_N;
int N, Nl, Nr;
int D[MAX_N][MAX_N];
int JR[MAX_N + 1][1 << 15]; // join_result[either some x to join with or CURR for latest rmask][lmask] for cache coherency
int LHS[1 << 15];
int RHS;
string s;

inline int LSOne (int a) {
    return (a & -a);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    srand(time(0));

    cin >> s;
    N = s.size();
    Nl = N / 2;
    Nr = N - Nl;

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            cin >> D[i][j];
            D[j][i] = D[i][j];
        }
    }

    int lmask = 0, rmask = 0;
    int E = 0; // Maintain current evaluation of the spell

    /* Gray code subset enum brute force on LHS */
    for (int i = 1; i <= (1 << Nl); ++i) {
        int d = __builtin_ctz(LSOne(i));

        /* Bookkeeping for current subset */
        LHS[lmask] = E;
        for (int r = 0; r < Nr; ++r) {
            JR[r][lmask] = 0;
            for (int l = 0, lm = 1; l < Nl; ++l, lm <<= 1) if (lm & lmask) JR[r][lmask] += D[l][Nl+r]; // cost of adding some r from RHS to lmask from LHS
        }

        /* Update current subset */
        if (lmask & LSOne(i)) { // in, remove
            for (int l = 0, lm = 1; l < Nl; ++l, lm <<= 1) if (lm & lmask) E -= D[d][l];
        } else { // not in, add
            for (int l = 0, lm = 1; l < Nl; ++l, lm <<= 1) if (lm & lmask) E += D[d][l];
            E += D[d][d];
        }
        lmask ^= LSOne(i);
    }

    E = 0;
    int best_E = 0;
    int best_mask = 0;

    /* Gray code subset enum brute force on RHS */
    for (int j = 1; j <= (1 << Nr); ++j) {
        int d = __builtin_ctz(LSOne(j));
        RHS = E;

        /* Try this rmask with every possible lmask to find best overall subset */
        for (lmask = 0; lmask < (1 << Nl); ++lmask) {
            int E_full = LHS[lmask] + RHS + JR[CURR][lmask];
            if (E_full > best_E) {
                best_E = E_full;
                best_mask = lmask | (rmask << Nl);
            }

            /* Update for next iteration based on modification*/
            JR[CURR][lmask] = (rmask & LSOne(j)) ? (JR[CURR][lmask] - JR[d][lmask])
                                                 : (JR[CURR][lmask] + JR[d][lmask]);
        }
            

        /* Update current subset */ 
        if (rmask & LSOne(j)) { // in, remove
            for (int r = 0, rm = 1; r < Nr; ++r, rm <<= 1) if (rm & rmask) E -= D[Nl + d][Nl + r];
        }
        else { // not in, add
            for (int r = 0, rm = 1; r < Nr; ++r, rm <<= 1) if (rm & rmask) E += D[Nl + d][Nl + r];
            E += D[Nl + d][Nl + d];
        }

        rmask = rmask ^ LSOne(j);
    }

    /* Convert best subset mask to letters */
    vector<char> chosen;
    for (int i = 0, im = 1; i < N; ++i, im <<= 1) if (best_mask & im) chosen.push_back(s[i]);

    /* Output results */
    cout << chosen.size() << endl;
    if (chosen.size() > 0) {
        for (char l : chosen) {
            cout << l;
        }
        cout << endl;
    }

    return 0;
}

