#include <bits/stdc++.h>
using namespace std;
int main() {
	int g,s,c; cin >> g; cin >> s; cin >> c;
	int total = 3*g + 2*s + c;	
	if (total >= 8) 
		cout << "Province or ";
	else if (total >= 5)
		cout << "Duchy or ";
	else if (total >= 2)
		cout << "Estate or ";
	
	if (total >= 6)
		cout << "Gold" << endl;
	else if (total >= 3)
		cout << "Silver" << endl;
	else
		cout << "Copper" << endl;
	return 0;
}
