#include <bits/stdc++.h>
using namespace std;
int main () {
	int N;
	while (N != 0) {
		cin >> N;
		for (int m = 1;m<N;m++) {
			int toOff = 0;
			int totalOff = 0;
			vector<bool> turnedOff(N,false);
			while (toOff != 12) {
				turnedOff[toOff] = true;
				totalOff++;
				for (int i = 0;i<m;i++) {
					toOff++;
					toOff %= N;
					while (turnedOff[toOff]) {
						toOff++;
						toOff %= N;
					}
				}
			}
			totalOff++;
			if (totalOff == N) {
				cout << m << endl;
				break;
			}
		}
	}
}