#include <bits/stdc++.h>
using namespace std;

ostream &operator << (ostream& o,vector<vector<int>> &v) {
	for (int i=0;i<v.size();++i) {
		for (int j=0;j<v[0].size();++j) {
			o << v[i][j];
			if (j != v[0].size()-1)
				o << " ";
		}
		if (i != v.size()-1)
			o << "\n";
	}
	return o;
}

int main() {
	int T; cin >> T;
	while (T--) {
		int H,W; scanf("%d %d",&H,&W);
		vector<vector<int>> grid(H,vector<int>(W,0));
		grid[0][1] = 0; 
		int i,j;
		for (i=1;i<W-1;i = i+2) {
			grid[0][i] = !grid[0][i-1];
			grid[0][i+1] = !grid[0][i-1];
		}
		grid[0][i] = !grid[0][i-1];
		
		
		for (j=1;j<H-1;j = j+2) {
			for (i=0;i<W;i++) {
				grid[j][i] = !grid[j-1][i];
				grid[j+1][i] = !grid[j-1][i];
			}
		}
		for (i=0;i<W;i++) {
			grid[j][i] = !grid[j-1][i];
		}
		
		cout << grid << endl;
		
	}
}