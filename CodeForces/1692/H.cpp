#include <bits/stdc++.h>
 
using namespace std;
 
long long INF = static_cast<long long>(1e17);
 
class SegmentTree {
    public:
        SegmentTree(int n):n(n) {
            L.assign(4*n,-1);
            R.assign(4*n,-1);
            pref.assign(4*n,-1);
            suff.assign(4*n,-1);
            best.assign(4*n,-1);
            r_pref.assign(4*n,-1);
            l_suff.assign(4*n,-1);
            sumAll.assign(4*n,-1);
            build(1,1,n);
            A.assign(n+1,-1);
        };
 
        void pointUpdate(int i, int upd) {
            pointUpdate(1,1,n,upd,i);
        }
 
        tuple<int, int, long long> bestQuery() {
            return make_tuple(L[1],R[1],best[1]);
        }
 
        void prettyPrint() {
            queue<int> bfsQ;
            bfsQ.push(1);
            while (bfsQ.size() > 0) {
                int curr = bfsQ.front(); bfsQ.pop();
                cout << "C: " << curr << " L: " << L[curr] << " R: " << R[curr] << " sumaLl: " << sumAll[curr] << ";" << endl;
                if (left(curr) < pref.size()) {
                    bfsQ.push(left(curr));
                    bfsQ.push(right(curr));
                }
            }
        }
 
    private:
        vector<int> L;
        vector<int> R;
        vector<int> A;
        vector<long long> pref;
        vector<long long> suff;
        vector<long long> best;
        vector<long long> sumAll;
        vector<int> r_pref;
        vector<int> l_suff;
        int n;
 
        void build(int i, int l, int r) {
            // cout << "L" <<  l << endl;
            if (l == r)  {
                L[i] = l;
                R[i] = l;
                pref[i] = -1;
                suff[i] = -1;
                best[i] = -1;
                sumAll[i] = -1;
                r_pref[i] = l;
                l_suff[i] = l;
            }
            else {
                build(left(i),l,(l+r)/2);
                build(right(i),(l+r)/2+1,r);
                merge(i);
            }
        }
 
        void pointUpdate(int i, int l, int r, int upd, int x) {
            if (l == r)  {
                A[x] = upd;
                L[i] = l;
                R[i] = l;
                pref[i] = upd;
                suff[i] = upd;
                best[i] = upd;
                sumAll[i] = upd;
                r_pref[i] = l;
                l_suff[i] = l;
            }
            else {
                int m = (l+r)/2;
                if (x <= m) {
                    pointUpdate(left(i),l,m,upd,x);
                }
                else {
                    pointUpdate(right(i),m+1,r,upd,x);  
                }  
                merge(i);
            }
        }
 
        void merge(int i) {
            int A = left(i);
            int B = right(i);
            long long childBest = max(best[A],best[B]);
 
            if (childBest > suff[A] + pref[B]) {
                best[i] = childBest;
                L[i] = (childBest == best[A]) ? L[A] : L[B];
                R[i] = (childBest == best[A]) ? R[A] : R[B];
            }
            else {
                best[i] = suff[A] + pref[B];
                L[i] = l_suff[A];
                R[i] = r_pref[B];
            }
 
            if (pref[A] > sumAll[A] + pref[B]) {
                pref[i] = pref[A];
                r_pref[i] = r_pref[A];
            }
            else {
                pref[i] = sumAll[A] + pref[B];
                r_pref[i] = r_pref[B];
            }
 
            if (suff[B] > sumAll[B] + suff[A]) {
                suff[i] = suff[B];
                l_suff[i] = l_suff[B];
            }
            else {
                suff[i] = sumAll[B] + suff[A];
                l_suff[i] = l_suff[A];
            }
 
            sumAll[i] = sumAll[A] + sumAll[B];
        }
 
        inline int left(int x) {
            return (x << 1);
        }
        inline int right(int x) {
            return (x << 1) + 1;
        }
 
};
 
 
int main() {
    int T;
    scanf("%d",&T);
    for (int t=0;t<T;++t) {
       int n;
       scanf("%d",&n);
       vector<int> nums(n);
       unordered_map<int,vector<int>> occs; 
       occs.reserve(n);

       for (int i=0;i<n;++i) {
        scanf("%d",&nums[i]);
        if (occs.count(nums[i]))
            occs[nums[i]].push_back(i+1);
        else    
            occs[nums[i]] = vector<int>(1,i+1);
       }
 
       SegmentTree st(n);
 
       int bestL;
       int bestR;
       int bestA = 0;
       long long bestScore = -INF;
 
    //    st.prettyPrint();
 
       for (auto [a, occsA] : occs) {
            
            for (int occ : occs[a]) {
                // cout << "pa" << a << " " << occ << endl;
                st.pointUpdate(occ,1);
            }
            
            auto [thisL, thisR, thisBest] = st.bestQuery();
            if (thisBest > bestScore) {
                bestScore = thisBest;
                bestA = a;
                bestL = thisL;
                bestR = thisR;
            }
            
            for (int occ : occs[a]) {
                st.pointUpdate(occ,-1);
            }
       }
       printf("%d %d %d\n",bestA, bestL, bestR);
    //    st.prettyPrint();
    }
 
 
    return 0;
}