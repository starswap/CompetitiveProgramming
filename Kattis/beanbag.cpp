#include <bits/stdc++.h>
using namespace std;

int B, T;
const int INF = (int) 1e9;
vector<bitset<101>> coverageOfABCD;
vector<int> needed;
bitset<101> allCovered = 0;


inline int LSOne(int a) {return a&-a;};

int bestSet(int idx, int setMask) {
    if (idx == B) { //Full subset created
        bitset<101> coverage = 0;

        int cost = 0;
        while (setMask != 0) {
            coverage |= coverageOfABCD[__builtin_ctz(LSOne(setMask))];
            cost += needed[__builtin_ctz(LSOne(setMask))];
            setMask ^= LSOne(setMask); 
        }
        if (coverage == allCovered) {
            return cost;
        }
        else {
            return INF;
        }
    }
    else {
        return min(bestSet(idx+1,setMask),bestSet(idx+1,setMask^(1<<idx)));
    }
}


int main() {
    scanf("%d",&B);

    int totalNeeded = 0;
    needed.assign(B,0);
    for (int b=0;b<B;++b) {
        cin >> needed[b];
        totalNeeded += needed[b];
    }

    scanf("%d",&T);

    coverageOfABCD.assign(B,bitset<101>(0));
    
    for (int t=0;t<T;++t) {
        int N; cin >> N;
        for (int n=0;n<N;++n) {
            int curr;
            cin >> curr;
            curr--;
            coverageOfABCD[curr].set(t+1);
        }
        if (N == 0) {
            for (int curr=0;curr<B;curr++)
                coverageOfABCD[curr].set(t+1);
        }
    }

    for (int i=1;i<=T;i++)
        allCovered.set(i);
    
    cout << totalNeeded - bestSet(0,0) << endl;
    

    return 0;
}