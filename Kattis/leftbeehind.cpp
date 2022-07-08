#include <bits/stdc++.h>
using namespace std;

int main() {
	int x,y;
	while (scanf("%d %d",&x,&y), x != 0 || y != 0) {
		if (x + y == 13)
			printf("Never speak again.\n");
		else if (y > x)
			printf("Left beehind.\n");
		else if (y == x)
			printf("Undecided.\n");
		else
			printf("To the convention.\n");
	}
	
}