#include <bits/stdc++.h>
using namespace std;

// Method: 
//      Each palindrome constraint can be phrased as saying that the first bit in the subrange equals the last bit in the subrange, the second bit equals the second-last bit, and so on.
//      Therefore we have a number of pairs of elements which must be equal. The same element can appear in multiple pairs, creating a larger subset of bits that must all be equal. (e.g. 1 == 3 == 5 == 7)
//      We can use UFDS to track these subsets of bits that must be equal. For each constraint (M), for each (nth,nth last) pair (N/2), we do a UFDS union (alpha ~ 5). This is O(MN)
//      We can then set each of these subsets of bits to be 0 or 1 in their entirety, and we want to do so minimising the difference between the number of zeroes and ones.
//      This load balancing is the same as saying we want the number of 0s to be as close to N/2 as possible, and we can choose this number by chosing some of the subsets of bits which will all be set to 0, and setting the rest as 1s.
//      We can use coin-change/0-1 knapsack pseudo-polynomial DP algorithm to select the subsets of bits that we want to make 0s in order to achieve a particular number of 0s in all. This is O(numberOfCoins * maximumValueWeCanBeAskedToMake). In this case that's O(N*N) in the worst case where we have no constraints on the bits (each subset is size 1), and we have to try all bits as 0. Note that these two cases are mutually exclusive so in reality it's better than that.
//      We start by trying numberOfZeroes=N/2. Then we do numberOfZeroes=N/2+1 and N/2-1 and so on. We have **no memo table reinitialisation** and thus this step can find the minimum difference in O(N^2) via DP, even if one iteration is up to N^2 and we are doing up to N of them.

vector<int> coins;
vector<int> parentToIndex;

class UFDS {
    private: 
        vector<int> p;
        vector<int> sizeOfSet;
        vector<int> rank;

        int n;
        

    public:
        UFDS(int n):n(n) {
            p.assign(n,0);
            rank.assign(n,1);
            sizeOfSet.assign(n,1);

            for (int i=0;i<n;++i) {
                p[i] = i;
                rank[i] = 1;
            }
        }

        void unionSet(int a, int b) {
            a = findSet(a);
            b = findSet(b);
         
            if (a == b) return;
            
            if (rank[a] == rank[b]) {
                rank[a]++;
                p[b] = a;
                sizeOfSet[a] += sizeOfSet[b];
            } else if (rank[a] < rank[b]) {
                p[a] = b;
                sizeOfSet[b] += sizeOfSet[a];
            } else {
                p[b] = a;
                sizeOfSet[a] += sizeOfSet[b];
            }
        }

        void getSetSizes() {
            unordered_set<int> setsEnumerated;
            
            for (int i=0;i<n;++i) {
                int set = findSet(i);
                if (!setsEnumerated.contains(set)) {
                    setsEnumerated.insert(set);
                    parentToIndex[set] = coins.size();
                    coins.push_back(sizeOfSet[set]);
                }
            }
        }


        int findSet(int i) {
            if (p[i] == i) return i;
            else {
                p[i] = findSet(p[i]);
                return p[i];
            }
        }

};


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
        UFDS indices(N);

        coins.clear();
        parentToIndex.assign(N,-1);
        
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
                indices.unionSet(X+i,Y-i);
            }
        }

        indices.getSetSizes();
        
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
            int set = indices.findSet(i);
            printf("%c",(setAllocations[parentToIndex[set]])); 
        }

        cout << endl;
    }
    return 0;
}
