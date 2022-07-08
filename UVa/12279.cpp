#include <bits/stdc++.h>
using namespace std;
int main() {
	int c = 1; int N = 1;
	while (cin >> N, N != 0) {
		int eb = 0;
		for (int i=0;i<N;++i) {
			int v; cin >> v;
			if (v == 0)
				eb--;
			else
				eb++;
		}
		printf("Case %d: %d\n",c,eb);
		c++;
	}
	
}