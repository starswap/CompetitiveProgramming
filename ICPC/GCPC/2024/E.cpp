#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

const int UNK = -1;

int x;

int DP[301][301][301][2][2]; // winning

bool doDP(int e, int t, int n, bool wants_even, bool is_even) {
    if (DP[e][t][n][wants_even][is_even] != UNK) {
        return DP[e][t][n][wants_even][is_even];
    } else if (e == 0 && t == 0) {
        return wants_even == is_even;
    } else {
        bool exists_losing_for_them = false;
        if (e > 0) {
            exists_losing_for_them |= !doDP(e - 1, t, n, !wants_even, true);
        }
        if (t > 0) {
            exists_losing_for_them |= !doDP(e, t - 1, n, !wants_even, !is_even);
        }
        if (n > 0) {
            exists_losing_for_them |= !doDP(e, t, n - 1, !wants_even, is_even);
        }
        DP[e][t][n][wants_even][is_even] = exists_losing_for_them;
        return exists_losing_for_them;
    }
}

multiset<pair<char, int>> toggles;
multiset<pair<char, int>> evens;
multiset<pair<char, int>> nothings;

char get_move(int e, int t, int n, bool wants_even, bool is_even) {
    if (e > 0 && !doDP(e - 1, t, n, !wants_even, true)) {
        return 'e';
    } else if (t > 0 && !doDP(e, t - 1, n, !wants_even, !is_even)) {
        return 't';
    } else if (n > 0 && !doDP(e, t, n - 1, !wants_even, is_even)) {
        return 'n';        
    } else {
        assert(1 == 0);
    }
}

bool is_even;
int n;
bool wants_even;

void read_move() {
    char c; int x;
    cin >> c >> x;

    if (c == '+' && x % 2 == 1) {
        toggles.erase(toggles.find(make_pair(c, x)));
        is_even = !is_even;
    } else if (c == '+' && x % 2 == 0) {
        nothings.erase(nothings.find(make_pair(c, x)));
    } else if (c == '*' && x % 2 == 1) {
        nothings.erase(nothings.find(make_pair(c, x)));
    } else if (c == '*' && x % 2 == 0) {
        evens.erase(evens.find(make_pair(c, x)));
        is_even = true;
    }

    n--;
}

void play_move() {
    char m = get_move(evens.size(), toggles.size(), nothings.size(), wants_even, is_even);

    if (m == 'e') {
        is_even = true;
        cout << evens.begin()->first << " " << evens.begin()->second << endl;
        evens.erase(evens.begin());
    } else if (m == 't') {
        is_even = !is_even;
        cout << toggles.begin()->first << " " << toggles.begin()->second << endl;
        toggles.erase(toggles.begin());
    } else {
        cout << nothings.begin()->first << " " << nothings.begin()->second << endl;
        nothings.erase(nothings.begin());
    }

    n--;
}



int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        int x; cin >> x;
        if (c == '+' && x % 2 == 1) {
            toggles.emplace(c, x);
        } else if (c == '+' && x % 2 == 0) {
            nothings.emplace(c, x);
        } else if (c == '*' && x % 2 == 1) {
            nothings.emplace(c, x);
        } else if (c == '*' && x % 2 == 0) {
            evens.emplace(c, x);
        } else {
            assert(1 == 0);
        }
    }
    cin >> x;
    is_even = !(x % 2);
    fill(&DP[0][0][0][0][0], &DP[0][0][0][0][0] + sizeof(DP) / sizeof(DP[0][0][0][0][0]), UNK);

    if (doDP(evens.size(), toggles.size(), nothings.size(), false, is_even)) {
        cout << "me" << endl;
        wants_even = false;
        play_move();
    } else {
        cout << "you" << endl;
        wants_even = true;
    }

    while (n > 0) {
        read_move();
        if (n == 0) break;
        play_move();
    }

    return 0;
}
