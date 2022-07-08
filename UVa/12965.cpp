#include <bits/stdc++.h>
using namespace std;
int main() {
	int tc; cin >> tc;
	while (tc--) {
		int P; int C;
		scanf("%d %d",&P,&C);
		vector<int> producers(P+1,0);
		vector<int> consumers(C);
		
		for (int p=0;p<P;++p) {
			cin >> producers[p];	
		}
		for (int c=0;c<C;++c) {
			cin >> consumers[c];	
		}
		
		
		sort(consumers.begin(),consumers.end());
		sort(producers.begin(),producers.end());
		int minAngry = 1e9;
		int setPrice;
		for (int p=0;p<P+1;++p) {
			int angryProducers = P - p;
			int angryConsumers = lower_bound(consumers.begin(),consumers.end(),producers[p]) - consumers.begin();
			int totalAngry = angryProducers + angryConsumers;
			if (totalAngry < minAngry) {
				minAngry = totalAngry;
				setPrice = producers[p];
			}
			
		}
		//if (minAngry == 1e9) { //no producers
		//	minAngry = 0; setPrice = 0;
		//}
		
		printf("%d %d\n",setPrice,minAngry);
		
	}
	
}