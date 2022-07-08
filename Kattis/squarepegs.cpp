#include <bits/stdc++.h>
using namespace std;
int main() {
	int N,M,K; scanf("%d %d %d",&N,&M,&K);
	vector<double> plots(N);
	vector<double> circHouses(M);
	
	for (int i=0;i<N;++i) {
		cin >> plots[i];
	}
	for (int i=0;i<M;++i) {
		cin >> circHouses[i];
	}
	for (int i=0;i<K;++i) {
		int x; cin >> x; 
		circHouses.push_back(sqrt(2)*static_cast<double>(x)/2.0);
	}	
	
	sort(circHouses.begin(),circHouses.end());
	sort(plots.begin(),plots.end());
	
	int plotNo = 0;
	int houseNo = 0;
	int total = 0;
	while (plotNo < N && houseNo < (M+K)) {
		if (circHouses[houseNo] < plots[plotNo]) {
			++total;
			++houseNo;
			++plotNo;
		} else {
			++plotNo;
		}
	}
	
	cout << total << endl;
	
}