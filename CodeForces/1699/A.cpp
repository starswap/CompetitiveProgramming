#include <bits/stdc++.h>
using namespace std;
int main() {
	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		if (N == 1) cout << -1 << endl;
		else 
			cout << 0 << " " << 1 << " " << (N^1) << endl;
	}
}