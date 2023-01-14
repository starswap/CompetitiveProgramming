// According to editorial

#include <bits/stdc++.h>
using namespace std;

string getNBits(const bitset<250>& bits, int n) {
    string res = "";
    for (int i=0;i<n;++i) {
        res += bits[i] ? '1' : '0';
    }
    return res;
}


int main() {
    int N;
    cin >> N;
    
    // vector<int> inDegree(N);
    vector<int> outDegree(N);
    
    set<pair<int,int>> masters;

    for (int n=0; n<N; ++n) {
        cout << "? " << n + 1 << " ";
        for (int i=0; i<N; ++i) {
            if (i == n) cout << '0';
            else cout << '1';
        }
        cout << endl;
        cin >> outDegree[n];
        // inDegree[n] = n - 1 - outDegree[n];

        masters.emplace(-outDegree[n], n);
    }

    bitset<250> mastersBits;
    mastersBits[masters.begin()->second] = 1;
    vector<int> pending;
    for (auto [degree, n] : masters) {
        if (n == masters.begin()->second) continue;

        string bits = getNBits(mastersBits, N);
        cout << "? " << n + 1 << " " << bits << endl;
        int wins;
        cin >> wins;
        if (wins) {
            for (int m : pending) {
                mastersBits[m] = 1;
            }
            mastersBits[n] = 1;
            pending.clear();
        }
        else {
            pending.push_back(n);
        }
    }

    cout << "! " << getNBits(mastersBits, N) << endl;  

    return 0;
}
