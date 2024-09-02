#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int po2less(int N) {
    int i = 1;
    while (i < N) {
        i *= 2;
    }
    i /= 2;
    return i;
}

int query(int a, int b, int c, int d) {
    cout << "? " << a << " " << b << " " << c << " " << d << endl;
    char res;
    cin >> res;
    if (res == '<') return -1;
    else if (res == '=') return 0;
    else return 1;
}

void answer(int a, int b) {
    cout << "! " << a << " " << b << endl;
}

// find maximum
// find all that are good with maximum
// find smallest of thsoe

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        int targ = po2less(N);

        int maxIndex = 0;
        for (int i = 1; i < N; ++i) {
            if (query(i, i, maxIndex, maxIndex) == 1) maxIndex = i;
        }

        vector<int> good_with_max;
        good_with_max.push_back(0);
        for (int i = 1; i < N; ++i) {
            int res = query(i, maxIndex, *good_with_max.begin(), maxIndex);
            if (res == 0) {
                good_with_max.push_back(i);
            } else if (res == 1) {
                good_with_max.clear();
                good_with_max.push_back(i);
            }
        }

        int minIndex = *good_with_max.begin();
        for (int v : good_with_max) {
            if (query(v, v, minIndex, minIndex) == -1) {
                minIndex = v;
            }
        }
        answer(minIndex, maxIndex);
    }
    return 0;
}




// use n - 1 queries to find 0 
// now find the one that has the most 1s by oring it with 0 - another n - 1 queries
// then or that with all of the ones that are only 1 one.

// find the biggest one

// find maximum (cost n queries)

// does nothi9ng to the maximum?

// find 1000000 by 

// find 0111111 by checking with 100000 - cost o(N) queries.

// min when xored with 0 is 1 (cost n queries)
