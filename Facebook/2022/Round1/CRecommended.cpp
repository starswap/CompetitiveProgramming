#include <bits/stdc++.h>
using namespace std;

class vec;
typedef vec point; 
template <class T>
ostream& operator << (ostream& o, vector<T> v);
ostream& operator << (ostream& o, point p);


long long K, D;
long long INF = LONG_LONG_MAX; 

class vec {
    public:
        long long x;
        long long y;

    vec(long long ax, long long ay):x(ax),y(ay){};
    vec():x(0),y(0){};

};

inline long long cross(const vec a, const vec b) {
    return a.x*b.y-a.y*b.x;
}

inline bool ccw(const point &a, const point &b, const point &c) {
    return cross(
        vec(b.x-a.x,b.y-a.y),
        vec(c.x-b.x,c.y-b.y)
    ) > 0;
}

bool pointsCMP(const point &a, const point &b) {
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

vector<point> AMC(vector<point> points) {

    sort(points.begin(),points.end(),pointsCMP);

    //Compute lower hull
    vector<point> stack;
    int n = 0;
    for (int i=0;i<points.size();++i) {
        while (n >= 2 && !ccw( stack[n-2], stack[n-1], points[i] ) ) {
            stack.pop_back();
            n--;
        }
        stack.push_back(points[i]);
        n++;
    }

    int sizeOfLowerHull = n;
    for (int i=points.size()-2;i>=0;--i) {
        while (n >= sizeOfLowerHull+1 && !ccw( stack[n-2], stack[n-1], points[i] ) ) {
            stack.pop_back();
            n--;
        }
        stack.push_back(points[i]);
        n++;
    }

    return stack;
}

ostream& operator << (ostream& o, point p) {
    o << "(" << p.x << "," << p.y << ")";
    return o;
}

template <class T>
ostream& operator << (ostream& o, vector<T> v) {
    o << "[";
    for (T i : v) {
        o << i;
        o << ",";
    }
    o << "]";
    return o;
}


inline long long getCost(int u, int v, const vector<point> &points) {
    return max(K, (points[u].x-points[v].x)*(points[u].x-points[v].x) + (points[u].y-points[v].y)*(points[u].y-points[v].y) );
}

inline bool connected(int u, int v, const vector<point> &points) {
    return (
        ( (points[u].x-points[v].x) * (points[u].x-points[v].x) + (points[u].y-points[v].y) * (points[u].y-points[v].y) ) < D*D
    );
}

inline void popPQArray(const unordered_set<int> &popped, const vector<long long> &costs, const int &N, long long &minCost, int &minIndex) {
    minCost = INF;
    minIndex = -1;
    for (int n=0;n<N;++n)
        if (costs[n] < minCost && !popped.contains(n)) {minCost = costs[n]; minIndex = n;}
}

long long doDijkstra(const vector<point> &points) {
    int N = points.size();
    vector<long long> costs(N,INF);
    costs[0] = 0;

    unordered_set<int> popped;

    long long minCost = INF;
    int minIndex = -1;
    popPQArray(popped,costs,N,minCost,minIndex);

    while (minIndex != N-1 && minIndex != -1) { // while there's still a chance of getting there and we haven't got there.
        // cout << costs << endl;
        // cout << "MI " << minIndex << endl;
        // // cout << minCost << endl;

        for (int n=0;n<N;++n) {
            // cout << (connected(n,minIndex,points) ? "conn" : "not conn") << endl;
            if (n != minIndex && !popped.contains(n) && connected(n,minIndex,points)) {
                // cout << "YES" << endl;
                // cout << getCost(minIndex,n,points) << endl;
                // cout << minCost << endl;
                long long relaxedCost = minCost+getCost(minIndex,n,points);
                // cout << relaxedCost << endl;
                // cout << "n" << n << endl;
                // cout << "Rc" << relaxedCost << endl;
                costs[n] = min(costs[n],relaxedCost);
            }
        }
        popped.insert(minIndex);
        popPQArray(popped,costs,N,minCost,minIndex);
    }

    if (minIndex == -1)
        return -1;
    else
        return minCost;
}


int main() {
    int T, N;
    scanf("%d",&T);
    for (int t=0;t<T;++t) {
        scanf("%d %lld %d",&N,&K,&D);
        vector<point> points(N);

        for (int n=0;n<N;++n) {
            scanf("%lld %lld",&(points[n].x),&(points[n].y)); 
        }

        // cout << points << endl;
        vector<point> CH = AMC(points);
        CH.pop_back();
        sort(CH.begin(),CH.end(),pointsCMP);

        // cout << CH << endl;
        long long ans = doDijkstra(CH);

        printf("Case #%d: %lld",t+1,ans);
        cout << endl;
        
    }
}
