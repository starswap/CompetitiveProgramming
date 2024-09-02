#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, X; cin >> N >> X;
        int op1 = N - X;
        int op2 = N + (X - 2);
        
        int i = 1;
        set<int> facts;
        while (i * i <= op1) {
            if (op1 % i == 0) {
                int k1 = (op1 / i + 2) / 2;
                int k2 = (i + 2) / 2;

                if (k1 != 1 && ((op1 / i + 2) % 2 == 0) && k1 >= X) {
                    facts.insert(k1);
                }
                if (k2 != 1 && ((i + 2) % 2 == 0) && k2 >= X) {
                    facts.insert(k2);
                }
            }
            i++;
        }
        i = 1;
        while (i * i <= op2) {
            if (op2 % i == 0) {
                int k1 = (op2 / i + 2) / 2;
                int k2 = (i + 2) / 2;

                if (k1 != 1 && ((op2 / i + 2) % 2 == 0) && k1 >= X) {
                    facts.insert(k1);
                }
                if (k2 != 1 && ((i + 2) % 2 == 0) && k2 >= X) {
                    facts.insert(k2);
                }
            }
            i++;
        }
        cout << facts.size() << endl;
    }
    return 0;
}

// Ks = [4, 5, 7, 10, 13, 14, 19, 20, 37, 40]
// for K in Ks:
//     N = 76
//     arr = ([i for i in range(1, K + 1)] + [i for i in range(K - 1, 1, -1)]) * N
//     print(K, arr[N - 1])
