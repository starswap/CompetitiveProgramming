#include <bits/stdc++.h>
using namespace std;

int LOGN;
const int ROOT = 0;
const int MAX_N = 200000;
const int MAXLOGN = 20;

int liftArr[MAX_N][MAXLOGN];
int depth[MAX_N];

vector<vector<int>> AL;

int lift(int u, int i) {
    if (0 <= u && u < MAX_N && 0 <= i && i < MAXLOGN) {
        return liftArr[u][i];
    }
    else {
        return -1;
    }
}

void dfs(int u, int d, int p) {
    depth[u] = d;

    liftArr[u][0] = p;
    for (int n=1;n<=LOGN;++n) {
        liftArr[u][n] = lift(lift(u,n-1),n-1);
    }

    for (int v : AL[u]) {
        if (v != p) {
            dfs(v,d+1,u);
        }
    }
}

void preprocessBinLift() {
    fill(&liftArr[0][0],&liftArr[0][0]+sizeof(liftArr)/sizeof(liftArr[0][0]),-1);
    fill(depth,depth+MAX_N,-1);
    dfs(ROOT,0,-1);
}

int binLiftLCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];

    for (int n=LOGN;n>-1;--n) {
        if (diff & (1 << n)) {
            u = lift(u,n);
        }
    }

    // now at the same level
    for (int i=LOGN;i>-1;--i) {
        if (lift(u,i) != lift(v,i)) {
            u = lift(u,i);
            v = lift(v,i);
        }
    }
    if (u == v)
        return u;
    else
        return lift(u,0);
}


int main() {
    int N;
    scanf("%d",&N);
    AL.assign(N,vector<int>());
    for (int n=0;n<N-1;++n) {
        int x,y;
        cin >> x >> y;
        x--; y--;
        AL[x].push_back(y);
        AL[y].push_back(x);
    }

    LOGN = ceil(log(N)/log(2.0)+1);
    preprocessBinLift();

    int Q;
    cin >> Q;
    for (int q=0;q<Q;++q) {
        int K;
        bool fail = false;

        cin >> K;
        int L,R;

        cin >> L;
        if (K == 1) {
            cout << "YES" << endl;
            continue;
        }
        cin >> R;
        L--;
        R--;
        
        for (int k=0;k<K-2;++k) {
            int X;
            cin >> X;
            X--;

            int LR = binLiftLCA(L,R);
            if (LR == L)
                swap(L,R);
            int LX = binLiftLCA(L,X);
            int RX = binLiftLCA(R,X);
            

            if ((LR == LX && RX == X || LR == LX && RX == R) || (LR == RX && LX == X || LR == RX && LX == L) || (LX == RX && LR == R)) {
                if (LX == RX && LR == R) {
                    R = X;
                }
                else if (LX == L) {
                    L = X;
                }
                else if (RX == R && !(LR == R)) {
                    R = X;
                }
            }
            else {
                fail = true;
            }
        }
        cout << ((fail) ? "NO" : "YES") << endl;
    }


    return 0;
}


