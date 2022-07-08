#include <bits/stdc++.h>
using namespace std;

int main() {
	int tc; scanf("%d",&tc);
	while (tc--) {
		int n; scanf("%d",&n);
		int ans = floor(abs(((((static_cast<double>(n)*567)/9+7492)*235/47)-498)/10));
		printf("%d\n",(ans%10));
	}

}
