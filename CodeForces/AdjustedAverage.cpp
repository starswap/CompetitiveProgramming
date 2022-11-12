#include <bits/stdc++.h>
using namespace std;
 
const double INF = 1e30;

int n,k;
double sample_total = 0;
double x_bar;
vector<int> samples;

multimap<double,pair<int,int>> pairSums;

double solve0() {
    return fabs(x_bar-static_cast<double>(sample_total)/static_cast<double>(n));
}

double solve1() {
    double subsetSumTarget = sample_total - (x_bar * (n-1));
    // cout << subsetSumTarget << endl;
    double bestDelta = INF;
    for (int i=0;i<n;++i) {
        bestDelta = min(bestDelta,fabs(subsetSumTarget - samples[i]));
    }
    return (bestDelta / static_cast<double>(n-1));
}

double solve2() {
    double subsetSumTarget = sample_total - (x_bar * (n-2));
    double bestDelta = INF;
    for (int i=0;i<n;++i) {
        for (int j=0;j<i;++j) {
            double thisPair = samples[i] + samples[j]; 
            bestDelta = min(fabs(subsetSumTarget - thisPair),bestDelta);
        }
    }
    return (bestDelta / static_cast<double>(n-2));
}

double solve3() {
    double subsetSumTarget = sample_total - (x_bar * (n-3));

    pairSums.clear();
    for (int i=0;i<n;++i) {
        for (int j=0;j<i;++j) {
            double thisPair = samples[i] + samples[j];
            pairSums.emplace(thisPair,make_pair(j,i));
        }
    }

    double bestDiff = INF;

    for (int m = 0;m < n; ++m) {
        double totalRemaining = subsetSumTarget - samples[m];

        auto it = prev(pairSums.lower_bound(totalRemaining));
        bool done = false;

        while (!done) {
            auto [diff,pr] = *it;
            auto [l,g] = pr;

            if (l != m && g != m) {
                done = true;
                bestDiff = min(bestDiff, fabs(totalRemaining - diff));
            }
            if (pairSums.begin() == it) {
                done = true;
            }
            it--;
        }

        it = pairSums.lower_bound(totalRemaining);
        done = false;

        while (!done) {
            auto [diff,pr] = *it;
            auto [l,g] = pr;

            if (l != m && g != m) {
                done = true;
                bestDiff = min(bestDiff, fabs(totalRemaining - diff));
            }
            if (prev(pairSums.end()) == it) {
                done = true;
            }
            it++;
        }
    }
    return (bestDiff/static_cast<double>(n-3));
}

double solve4() {
  double subsetSumTarget = sample_total - (x_bar * (n-4));
  double bestDiff = INF;

    pairSums.clear();
    for (int i=0;i<n;++i) {
        for (int j=0;j<i;++j) {
            double thisPair = samples[i] + samples[j];
            pairSums.emplace(thisPair,make_pair(min(i,j),max(i,j)));
        }
    }


    for (int m = 0; m < n; ++m) {
        for (int l = 0; l < m; ++l) {
            double totalRemaining = subsetSumTarget - samples[m] - samples[l];

            auto it = prev(pairSums.lower_bound(totalRemaining));
            bool done = false;

            while (!done) {
                auto [diff,pr] = *it;
                auto [lo,hi] = pr;

                if (lo != m && hi != m && lo != l && hi != l) {
                    done = true;
                    bestDiff = min(bestDiff,fabs(totalRemaining - diff));
                }
                if (pairSums.begin() == it) {
                    done = true;
                }
                it--;
            }

            it = pairSums.lower_bound(totalRemaining);
            done = false;

            while (!done) {
                auto [diff,pr] = *it;
                auto [lo,hi] = pr;

                if (lo != m && hi != m && lo != l && hi != l) {
                    done = true;
                    bestDiff = min(bestDiff,fabs(totalRemaining - diff));
                }
                it++;
                if (it == pairSums.end()) {
                    done = true;
                }
            }
        }
    }
    return (bestDiff/static_cast<double>(n-4));
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    scanf("%d %d %lf",&n,&k,&x_bar);
    samples.assign(n,0);
    for (int i=0;i<n;++i) {
        scanf("%d",&samples[i]);
    }
    for (int i=0;i<n;++i) {
        sample_total += samples[i];
    }

    double bestAns = INF;
    bestAns = min(bestAns,solve0());
    bestAns = min(bestAns,solve1());

    // cout << solve0() << endl;
    // cout << solve1() << endl;
    // cout << solve2() << endl;
    // cout << solve3() << endl;
    // cout << solve4() << endl;
    
    if (k >= 2)
        bestAns = min(bestAns,solve2());
    if (k >= 3)
        bestAns = min(bestAns,solve3());
    if (k >= 4)
        bestAns = min(bestAns,solve4());

    printf("%lf\n",bestAns);
    
    return 0;
}