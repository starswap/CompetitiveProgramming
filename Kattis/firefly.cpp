#include <bits/stdc++.h>
using namespace std;

template <class T>
ostream& operator << (ostream& o,vector<T> v) {
	o << "[";
	for (int i=0;i<v.size();++i) {
		o << v[i] << ",";
	}
	o << "]";
	return o;
}

int main() {
	int N,H; cin >> N; cin >> H;
	vector<int> t(N/2);
	vector<int> m(N/2);
	for (int i=0;i<N/2;++i) {
		cin >> m[i]; cin >> t[i];
	}
	sort(m.begin(),m.end());
	sort(t.begin(),t.end());
	
//	cout << m << endl; cout << t << endl;

	vector<int> h(H+2,0);
	int currentHeight = 0; //previous highest stalagmite
	for (int i=0;i<N/2;++i) { //for all stalagmites in order
		//cout << h << endl;
		if (m[i] > currentHeight){ //if higher than previous highest
			
			for (int j=currentHeight+1;j<=m[i];++j) //all heights up to and including new heighest have known number of remaining obstacles.
				h[j] += N/2 - i;
			currentHeight = m[i]; //update highest
		}
	}
	
	int currentLength = 0; 
	for (int i=0;i<N/2;++i) {
	//	cout << h << endl;
		if (t[i] > currentLength){ //if longer than prev longest
			for (int j=currentLength+1;j<=t[i];++j) //
				h[H-j+1] += N/2 - i;
			currentLength = t[i]; //update highest
		}
	}	
	//cout << h << endl;
	
	
	int minObst = 200001;
	int noPlaces = 0;
	for (int i=1;i<=H;++i) {
		if (h[i] < minObst) {
			minObst = h[i];
			noPlaces = 1;
		} else if (h[i] == minObst) {
			noPlaces++;
		}
	}
	
	printf("%d %d",minObst,noPlaces);
	
}