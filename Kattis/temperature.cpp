#include <bits/stdc++.h>

using namespace std;

int main() {
	int X,Y; scanf("%d",&X); scanf("%d",&Y);
	if (Y == 1 && X == 0)
		printf("ALL GOOD\n");
	else if (Y == 1)
		printf("IMPOSSIBLE");
	else {
		printf("%f",static_cast<double>(X)/(1-static_cast<double>(Y)));
	}
	return 0;
}