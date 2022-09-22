#include <bits/stdc++.h>
using namespace std;

int N, M, K, A, B, R1, C1, R2, C2;

bool canForceHimToSurrender() {
    if (N == 1 || M == 1) return true;
    else if (K == 1) return false;
    else {
        int delta1 = abs(A-R1) + abs(B-C1); //Here we say they can force him to surrender iff the number of squares from Mr X to each agent is even - which is the same as saying they are on the same colour chess squares. The answers say Mr X is caught iff the even/oddness of the total distance from the top left square to Mr X. and each of the two agents is the same, which is clearly the same thing as saying they have to be on the same chessboard square colours, and thus the same as my method.
        int delta2 = abs(A-R2) + abs(B-C2);
        return (delta1 % 2 == 0) && (delta2 % 2 == 0);
    }
}

int main() {
    int T;
    scanf("%d",&T);
    for (int t=1;t<=T;++t) {
        scanf("%d %d %d",&N,&M,&K);
        scanf("%d %d",&A,&B);
        scanf("%d %d",&R1,&C1);

        if (K == 1) {
            R2 = C2 = 0;
        }
        else {
            scanf("%d %d",&R2,&C2);
        }
        printf("Case #%d: %c\n",t, (canForceHimToSurrender()) ? 'Y' : 'N');
    }
}