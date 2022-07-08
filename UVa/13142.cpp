#include <bits/stdc++.h>
using namespace std;
int main() {
	int t; cin >> t;
	while (t--) {
		long long T,S,D; cin >> T; cin >> S; cin >> D;
		long long m = (D*1000000)/(T*24*3600);
	//	cout << m << endl;
		cout << ((m > 0) ? "Remove " : "Add ") << abs(m) << " tons" << endl;
	}

}