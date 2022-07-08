#include <bits/stdc++.h>
using namespace std;
int main() {
	int T; cin >> T;
	while (T--) {
		long long w; cin >> w;
		printf("%lld\n",static_cast<long long>(floor((-1+sqrt(1+8*w))/2)));
	}
	return 0;
}