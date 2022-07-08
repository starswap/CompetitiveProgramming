#include <bits/stdc++.h>
using namespace std;

int main() {
	int N,K; scanf("%d %d",&N,&K);
	
	int total = 0;
	vector<vector<int>> deceptionLevels(K,vector<int>(N));
	vector<int> deceptionLevels(K,vector<int>(N));
	
	for (int i=0;i<K;++i) {
		for (int j=0;j<N;++j) {
			cin >> deceptionLevels[i][j];			
		}
	}

	for (int n=0;n<N;++n) {
		int base = 0;
		for (int j=0;j<K;++j) {
			base ^= deceptionLevels[j][n];
		}
		
		int best = base;
		for (int j=0;j<K;++j) {
			base ^= deceptionLevels[j][n];
			best = min(best,base);
			base ^= deceptionLevels[j][n];
		}
		cout << best << endl;
		total += best;		
	}
	
	cout << total << endl;
}