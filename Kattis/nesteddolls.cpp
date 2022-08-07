// We need an OST I think not just a BST since we need to be able to check where a key /would go/ even when it is not already present. 

//Greedy with PQ method: Sort in order to maintain the invariant that:
// "For any doll, all dolls after it in sequence cannot be nested in it" and therefore "all dolls that can be nested in a given doll (and possibly some that can't) come before it in sequence".
// Then iterate linearly over the dolls and for each one nest the largest one that is available to be nested inside it; we use an Order Statistics Tree to achieve this goal.

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

auto comp = []( pair<int,int> a, pair<int,int> b) {
    return a.second <= b.second;
}; 

typedef tree<pair<int,int>, null_type, decltype(comp), rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;

int main() {
  int T,M; scanf("%d",&T);
  while (T--) {
    scanf("%d",&M);
    vector<pair<int,int>> dolls;
    for (int i=0;i<M;++i) {
      int w,h; scanf("%d %d",&w,&h);
      dolls.emplace_back(w,h);
    }

    
    sort(dolls.begin(),dolls.end());
    
    ordered_multiset dollsPQ(comp);

    for (int i=0;i<M;++i) {
      if ((dollsPQ.size() > 0 && dollsPQ.begin()->first < dolls[i].first && dollsPQ.begin()->second < dolls[i].second)) {
        auto curr = prev(dollsPQ.end());
        int best = dollsPQ.order_of_key(dolls[i])-1;
        dollsPQ.erase(dollsPQ.find_by_order(best));
      }

      if (!(i < M-1 && dolls[i].first == dolls[i+1].first)) {
        int j = i;
        while (dolls[j].first == dolls[i].first) {
          dollsPQ.insert(dolls[j]);
          j--;
        }
      }
      
    }
    cout << dollsPQ.size() << endl;
  }
}
