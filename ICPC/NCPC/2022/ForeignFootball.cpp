#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    scanf("%d",&n);
    vector<vector<string>> grid;

    int sumOfAll = 0;
    for (int n=0;n<N;n++) {
        for (int nj=0;nj<N;++nj) {
            cin >> grid[n][nj];
            if (grid[n][nj] != "*") sumOfAll += grid[n][nj].size()
        }
    }

    if (n == 2) {

    }
    else {
        int totalLength = sumOfAll / (n-1);
        for (int n=0;n<N;++n) {
            int currSum = 0;
            for (int nj=0;nj<N;++nj) {
                if (grid[n][nj] != "*") currSum += grid[n][nj].size()
            }
            int currLength = (currSum - totalLength)/(n-2);
            

        }
        vector<int> lengths;

    }
    // find total length
    // (n-1) * totalLength
    // each one is sigmaL + (n-2) * length 
    return 0;
}