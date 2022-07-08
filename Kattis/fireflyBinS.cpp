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

	
	int minObst = 200001;
	int noPlaces = 0;
	for (int i=1;i<=H;++i) {
		int im = lower_bound(m.begin(),m.end(),i) - m.begin(); // index of first stalagmite which would have to be broken = no which don't have to be.
		int it = lower_bound(t.begin(),t.end(),H-i+1) - t.begin(); //index of first stalactite which would have to be broken = no which don't have to be.
		
		int h = N - im - it; // total broken at this height
		
		if (h < minObst) {
			minObst = h;
			noPlaces = 1;
		} else if (h == minObst) {
			noPlaces++;
		}
	}
	
	printf("%d %d",minObst,noPlaces);
	
}