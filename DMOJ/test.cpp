#include <bits/stdc++.h>
using namespace std;

int main() {
	clock_t begin = clock();
	bitset<10000100> myBitset(255555555555);
	
	unordered_set<bitset<10000100>> a;
	a.insert(myBitset);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin); // / CLOCKS_PER_SEC;
	cout << "Longer " << time_spent << endl;
	
	
	
	begin = clock();
	bitset<1010> myBitset2(255567);
	
	unordered_set<bitset<1010>> b;
	b.insert(myBitset2);
	
	end = clock();
	time_spent = (double)(end - begin); // / CLOCKS_PER_SEC;
	cout << "Shorter " << time_spent << endl;	
}

