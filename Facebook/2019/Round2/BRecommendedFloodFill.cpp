#include <bits/stdc++.h>
using namespace std;

//Instead of the UFDS method as outlined in my original code (B.cpp) we can use flood fill to determine which bits have to be the same, which is the suggested method in the solutions. Here's the code to do that:
//Time taken to AC: Also 3.9 seconds as with the other method - there is very little to separate them. Except this code is shorter and easier to get right.
//In theory the flood fill should only visit unvisited nodes and so should be O(N). Therefore it should be slightly faster than the UFDS method. 


vector<int> coins;
vector<int> itemToSetIndex;

vector<vector<int>> AL;
vector<int> visited;

int floodFillToGetSetSizes(int u,int setNo) {
    
    itemToSetIndex[u] = setNo;
    visited[u] = 1;

    int totalNodes = 1;
    for (int v : AL[u]) {
        if (!visited[v])
            totalNodes += floodFillToGetSetSizes(v,setNo);
    }
    return totalNodes;
}

const int IDX_MAX = 4001;
const int RZ_MAX = 4001;

int dp[IDX_MAX][RZ_MAX];

bool loadBalanceSubsetSum(int idx, int remainingZeroes) {
    if (remainingZeroes < 0) {return 0;} 
    if (idx == coins.size() && remainingZeroes == 0) {return 1;}
    if (idx == coins.size()) {return 0;}
    if (dp[idx][remainingZeroes] != 2) {return dp[idx][remainingZeroes];}
    else {
        dp[idx][remainingZeroes] = loadBalanceSubsetSum(idx+1,remainingZeroes-coins[idx]) || loadBalanceSubsetSum(idx+1,remainingZeroes);
        return dp[idx][remainingZeroes];
    }
}

vector<char> setAllocations;
void allocateDP(int idx, int remainingZeroes) {
    if (remainingZeroes < 0) {return;} 
    if (idx == coins.size()) {return;}
    else {
        if (loadBalanceSubsetSum(idx+1,remainingZeroes-coins[idx]) ) { //TAKe as 0
            setAllocations[idx] = '0';
            allocateDP(idx+1,remainingZeroes-coins[idx]);
        }
        else { //Don't take as 0;
            setAllocations[idx] = '1';
            allocateDP(idx+1,remainingZeroes);
        }
    }
}

int main() {
    int T;
    scanf("%d",&T);

    for (int t=1;t<=T;++t) {
        int N,M;
        scanf("%d %d",&N,&M);

        coins.clear();
        itemToSetIndex.assign(N,-1);

        AL.assign(N,vector<int>());
        visited.assign(N,0);

        for (int i=0;i<IDX_MAX;i++) {
            for (int r=0;r<RZ_MAX;r++) {
                dp[i][r] = 2;
            }
        }


        for (int m=0;m<M;++m) {
            int X,Y;
            scanf("%d %d",&X,&Y);
            X--;
            Y--;

            for (int i=0;i<=(Y-X)/2;++i) {
                AL[X+i].push_back(Y-i);
                AL[Y-i].push_back(X+i);
            }
        }

        int setNo = 0;
        for (int u=0;u<N;++u) {
            if (!visited[u]) {
                coins.push_back(floodFillToGetSetSizes(u,setNo));
                setNo++;
            }
        }

        int numZeroes;
        for (int delta=0;delta<N;delta++) {
            numZeroes = N/2+delta;
            if (loadBalanceSubsetSum(0,numZeroes)) break;
            numZeroes = N/2-delta;
            if (loadBalanceSubsetSum(0,numZeroes)) break;            
        }
        
        setAllocations.assign(coins.size(),'A');
        allocateDP(0,numZeroes);

        printf("Case #%d: ",t);
        
        for (int i=0;i<N;++i) {
            printf("%c",(setAllocations[itemToSetIndex[i]])); 
        }

        cout << endl;
    }
    return 0;
}
