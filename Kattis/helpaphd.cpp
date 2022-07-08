#include <bits/stdc++.h>
using namespace std;
int main() {
	int t; scanf("%d",&t);
	while (t--) {
		int a,b;
		if (scanf("%d+%d",&a,&b))
			printf("%d\n",a+b);
		else {
			string dummy; cin >> dummy;
			cout << "skipped" << endl;
		}
		
	}
	return 0;
}