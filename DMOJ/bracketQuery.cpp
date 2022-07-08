#include <bits/stdc++.h>
using namespace std;

int main() {
	int N,Q; cin >> N; cin >> Q;
	string S;
	cin >> S;
	
	vector<int> totalLeft(N+1,0);
	vector<int> totalRight(N+1,0);
	vector<int> unmatchedLeft(N+1,0);
	vector<int> unmatchedRight(N+1,0);
	
	int l=0;
	int r=0;
	int tl=0;
	int tr=0;
	
	for (int i=1;i<=N;++i) {
		if (S[i-1] == '(') {
			if (r == 0) {			
				l++;
			} else {
				r--;
			}
			++tl;
		} else if (S[i-1] == ')') {
			if (l == 0) {			
				r++;
			} else
				l--;
			++tr;
		}
		
		totalLeft[i] = tl;
		totalRight[i] = tr;
		unmatchedLeft[i] = l;
		unmatchedRight[i] = r;
	}
	
	for (int q=0;q<Q;++q) {
		int L,R; cin >> L; cin >> R;
		int totalExtraLeft = (unmatchedLeft[R] - unmatchedLeft[L-1]) + (totalLeft[R]-totalLeft[L-1]) - (totalRight[R]-totalRight[L-1]);
		int totalExtraRight = (unmatchedRight[R] - unmatchedRight[L-1]) + (totalRight[R]-totalRight[L-1]) - (totalLeft[R]-totalLeft[L-1]);
		cout << ((totalExtraLeft == 0 || totalExtraRight == 0) ? "YES" : "NO") << endl;
	}
}