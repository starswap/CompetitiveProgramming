#include <bits/stdc++.h>
using namespace std;
int main() {
	int n,m;
	cin >> n; cin >> m;
	vector<long long> sizes(n);
	for (int i=0;i<n;++i) {
		cin >> sizes[i];
	}
	sort(sizes.begin(),sizes.end());
	long long total = 0;
	for (int j=0;j<m;++j) {
		long long a; cin >> a;
		total += *lower_bound(sizes.begin(),sizes.end(),a) - a;
	}
	cout << total << endl;
}