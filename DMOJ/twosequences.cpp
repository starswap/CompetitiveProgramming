#include <bits/stdc++.h>
using namespace std;

int main() {
	int N,Q; scanf("%d %d",&N,&Q);
	vector<int> A(N+1,0);
	vector<int> B(N+1,0);
	vector<int>	accA(N+1,0);
	vector<int> accB(N+1,0);
	
	int total = 0;
	for (int i=1;i<=N;++i) {
		cin >> A[i];
		total += A[i];
		accA[i] = total;
	}
	total = 0;
	for (int i=1;i<=N;++i) {
		cin >> B[i];
		total += B[i];
		accB[i] = total;
	}
	
	for (int q=0;q<Q;++q) {
		int L,R;
		cin >> L; cin >> R;
		
		int lo = L;
		int hi = R-1;
		
		int K;
		while (lo != hi) {
			K = (lo+hi)/2;
			int diff = (accA[K] - accA[L-1]) - (accB[R] - accB[K]);
			(diff >= 0) ? hi = K : lo = K+1;
		}
		K = lo;
		int diff = (accA[K] - accA[L-1]) - (accB[R] - accB[K]);
		if (diff == 0)
			cout << accA[K] - accA[L-1] << endl;
		else if (diff > 0 && K > L) // A is bigger so also try A being 1 less large.
			cout << min(max((accA[K-1] - accA[L-1]),(accB[R] - accB[K-1])),max((accA[K] - accA[L-1]),(accB[R] - accB[K]))) << endl;
		else if (K < R-1)// B is bigger so also try A being 1 larger.
			cout << min(max((accA[K+1] - accA[L-1]),(accB[R] - accB[K+1])),max((accA[K] - accA[L-1]),(accB[R] - accB[K]))) << endl;
		else {
			cout << max((accA[K] - accA[L-1]),(accB[R] - accB[K])) << endl;
		}
	}
	
}