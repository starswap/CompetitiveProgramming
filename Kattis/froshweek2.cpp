#include <bits/stdc++.h>
using namespace std;

int main() {
	int N,M; scanf("%d %d",&N,&M);
	vector<int> tasks(N);
	vector<int> intervals(M);
	
	for (int i=0;i<N;++i) {
		cin >> tasks[i];
	}
	for (int j=0;j<M;++j) {
		cin >> intervals[j];
	}	
	
	sort(tasks.begin(),tasks.end());
	sort(intervals.begin(),intervals.end());
	
	int total = 0;
	int currentI = 0;
	int currentT = 0;
	
	while (currentT < N && currentI < M) {
		if (tasks[currentT] <= intervals[currentI]) {
			++total; ++currentT; ++currentI;
		}
		else {
			++currentI;
		}
	}
	
	cout << total << endl;
}