#include <bits/stdc++.h>
using namespace std;

int main() {
	int tc;
	cin >> tc;
	while (tc--) {
		float r,c;
		cin >> r; cin >> c;
		printf("%d\n",static_cast<int>((ceil((r-2)/3)*ceil((c-2)/3))));
	}
}