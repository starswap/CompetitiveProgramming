#include <bits/stdc++.h>
using namespace std;

vector<int> coins;
int N;
vector<bool> selected;

int withdraw(int X,int start=N-1) { //would need to adjust to use mod etc but still doesn't work. 
	if (X == 0) return 0;
	int i;
	for (i=start;i>=0;--i) {
		if (coins[i] <= X)
			break;
	}
	int Y = coins[i];
	if (selected[i])
		return withdraw(X-Y,i);
	else {
		selected[i] = true;
		return 1+withdraw(X-Y,i);
	}
}


int main() {
	int T; cin >> T;
	while (T--) {
		cin >> N;
		coins.resize(N);
		selected.resize(N);
		fill(selected.begin(),selected.end(),false);
		for (int i=0;i<N;++i) {
			cin >> coins[i];
		}
		
		int total = 0;
		
		for (int i=N-1;i>=0;--i) {
			fill(selected.begin(),selected.end(),false);
			int before = withdraw(total);
			fill(selected.begin(),selected.end(),false);
			int after = withdraw(total+coins[i]);
			if (after > before) {
		//		cout << coins[i] << endl;
				total += coins[i];
			}
		}
		fill(selected.begin(),selected.end(),false);
		cout << withdraw(total) << endl;
		
	}	
}
