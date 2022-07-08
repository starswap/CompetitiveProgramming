#include <bits/stdc++.h>
using namespace std;

double price(int k, int p, int a, int b, int c, int d) {
	 return p * (sin(a*k + b) + cos(c*k + d) + 2);
}

int main() {
	int p,a,b,c,d,n;
	
	while (!cin.eof()) {
		double maxDec = 0;
		cin >> p, cin >> a, cin >> b, cin >> c, cin >> d, cin >> n;
		double maxi = price(1,p,a,b,c,d);
		double curr;
		for (int i=2;i<=n;++i) {
			curr = price(i,p,a,b,c,d);
			maxDec = max(maxi - curr,maxDec);
			maxi = max(maxi,curr);
		}
		printf("%.6f\n",maxDec);
	}
	
	return 0;
}



