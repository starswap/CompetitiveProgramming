#include <bits/stdc++.h>
using namespace std;

double fact(int n) {
	if (n == 1) {
		return 1;
	} else if (n >= 13) {
		return 1e9 + 1;
	}
	else {
		return n*fact(n-1);
	}
}

int main() {
	
	int m,n,t; cin >> m; cin >> n; cin >> t;
	double (*fnPtr)(int);
	switch (t) {
		case 1: {
			fnPtr = &fact; break;
		};
		case 2: {
			fnPtr = [](int a){ if (a >= 30) {return 1e9 + 1;} else {return static_cast<double>(1<<a);}}; break;
		};
		case 3: {
			fnPtr = [](int a){return static_cast<double>(pow(a,4));}; break;
		}
		case 4: {
			fnPtr = [](int a){return static_cast<double>(pow(a,3));}; break;
		}
		case 5: {
			fnPtr = [](int a){return static_cast<double>(pow(a,2));}; break;
		}
		case 6: {
			fnPtr = [](int a){return static_cast<double>((a*log(a)/log(2)));}; break;
		}
		case 7: {
			fnPtr = [](int a){return static_cast<double>(a);}; break;
		}
	}
	
	//cout << fnPtr(n) << endl;
	if (fnPtr(n) <= m) {
		cout << "AC" << endl;
	} else {
		cout << "TLE" << endl;
	}
	
	return 0;
}