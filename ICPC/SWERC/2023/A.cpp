#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
vector<int> suitIdxs = {0, 1, 2, 3};

const int INF = 10000000;

enum Suit {S, W, E, R, C};
istream& operator >>(istream& i, Suit& s) {
    char c;
    i >> c;
    switch (c) {
        case 'S': s = S; return i;
        case 'W': s = W; return i;
        case 'E': s = E; return i;
        case 'R': s = R; return i;
        case 'C': s = C; return i;
    }
}

ostream& operator <<(ostream& o, Suit& s) {
    switch (s) {
        case S: o << 'S'; return o;
        case W: o << 'W'; return o;
        case E: o << 'E'; return o;
        case R: o << 'R'; return o;
        case C: o << 'C'; return o;
    }
}

struct Card {
    Suit s;
    int value;

    friend istream& operator >>(istream& i, Card& c) {
        i >> c.s >> c.value;
        return i;
    }
    friend ostream& operator <<(ostream& o, Card& c) {
        o << c.s << c.value;
        return o;
    }
};

template <typename T>
int lis(const vector<T>& A, int N, function<bool(T, T)> lt) {
    int k = 0;
    vector<T> endValLengthL(N);
    vector<int> endILengthL(N, 0);

    for (int i = 0; i < N; ++i) {
        int ind = lower_bound(endValLengthL.begin(),endValLengthL.begin()+k, A[i], lt) - endValLengthL.begin(); //first index in array where the value is greater than this one, or we need to place a new one.
        endValLengthL[ind] = A[i];
        endILengthL[ind] = i;
        if (ind == k) {
            k++;
        }
    }
    return k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<Card> cards(N);
    for (int n = 0; n < N; ++n) {
        cin >> cards[n];
    }
    
    int best = INF;
    function<bool(Card, Card)> comp = [](Card c1, Card c2) {
        if (c1.s == c2.s) return c1.value < c2.value;
        else if (c1.s == C) return false;
        else if (c2.s == C) return true;
        else return (suitIdxs[c1.s] < suitIdxs[c2.s]);
    };

    do {
        best = min(best, N - lis(cards, N, comp));
    } while (std::next_permutation(suitIdxs.begin(), suitIdxs.end()));
    cout << best << endl;
    return 0;
}