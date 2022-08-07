//We need PBDS so we can check the one before a key that is not present.

//Variant of Interval covering with multiple tracks -> Use standard "sort by endpoint" technique, but how do we allocate to each track?
//Maintain OST (GNU PBDS) of the tracks' finish time (when they start being free) and allocate each new task, if it can be allocated, to the latest-free track which can accommodate it.


#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;
 

int main() {
	int N,K; cin >> N; cin >> K;
	
	vector<pair<int,int>> activities;
	for (int n=0;n<N;n++) {
		int s,f; cin >> s; cin >> f;
		activities.emplace_back(f,s);
	}
	sort(activities.begin(),activities.end());
	
	
	ordered_multiset freeFrom;
	
	for (int i=0;i<K;++i)
		freeFrom.insert(-1);
	
	int total = 0;
	for (int i=0;i<N;++i) {
		int best = freeFrom.order_of_key(get<1>(activities[i])) -1;
		if (best >= 0) { //a track is free when this event starts
			total++;
			freeFrom.erase(freeFrom.find_by_order(best));
			freeFrom.insert(get<0>(activities[i]));
		}
	}
	
	cout << total << endl;
	

}