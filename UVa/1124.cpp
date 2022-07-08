#include <bits/stdc++.h>
using namespace std;
int main() {
	string inp;
	bool first = true;
	while (!cin.eof()) {
		if (first) {first = false;}
		else {
			cout << endl;
		}
		getline(cin,inp);
		
		cout << inp;
	}
}