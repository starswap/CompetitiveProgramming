#include <bits/stdc++.h>
using namespace std;
int main() {
	int d; cin >> d;
	int min = 1e9+1;
	int minD = 0;
	for (int i=0;i<d;++i) {
		int a; cin >> a;
		if (a < min) {
			min = a;
			minD = i;
		}
	}
	cout << minD << endl;
	

}