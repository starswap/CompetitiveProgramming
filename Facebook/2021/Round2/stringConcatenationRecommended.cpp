// Using the method recommended in "Solution"

// Refactor to reduce globals where justified; reduce parameters where possible;
// avoid ignoring return value. lengths / stringLengths Check complexity

// Try optimising even just the basic one, then the better ones one at a time.
// Check video points to learn
// Check provided C++ solution.

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
//#pragma GCC optimize("unroll-loops")

#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    OST;

inline int LSOne(int a) {
  if (a == 0)
    return 0;
  return (a & -a);
}

int N, K;
vector<int> stringLengths;
unordered_set<int> thread1;
unordered_set<int> thread2;

// int callCount = 0;

bool solveFor25(const vector<int> &indices) {

  int total = 0;
  int bitString = 0;

  unordered_map<int, int> sumToBitString;

  bool found = false;
  for (int i = 1; i < (1 << indices.size());
       ++i) { // generate all subsets using the optimisation which means we
              // track the sum as we go along.
    if (bitString & LSOne(i)) // added so remove
      total -= stringLengths[indices[__builtin_ctz(LSOne(i))] - 1];
    else // removed so add
      total += stringLengths[indices[__builtin_ctz(LSOne(i))] - 1];
    bitString ^= LSOne(i);

    if (sumToBitString.find(total) != sumToBitString.end()) {
      found = true;
      break; // found two the same
    }
    sumToBitString[total] = bitString;
  }
  if (found) {
    int BS1 = bitString - (bitString & sumToBitString[total]);
    int BS2 = sumToBitString[total] - (bitString & sumToBitString[total]);
    while (BS1 > 0) {
      int twoPowV = LSOne(BS1);
      int v = __builtin_ctz(twoPowV);
      thread1.insert(indices[v]);
      BS1 ^= twoPowV;
    }
    while (BS2 > 0) {
      int twoPowV = LSOne(BS2);
      int v = __builtin_ctz(twoPowV);
      thread2.insert(indices[v]);
      BS2 ^= twoPowV;
    }
    return true;
  } else
    return false;
}

void solveFor100(const vector<int> &indicesOuter) {
  // callCount++;
  vector<int> indices;
  int index = 0;

  while (index < indicesOuter.size()) {
    while (indices.size() < 25 &&
           index < indicesOuter.size()) { // build up a subset of 25 which we
                                          // know will contain two threads
      indices.push_back(indicesOuter[index]);
      index += 1;
    }
    solveFor25(indices); // find two threads
    vector<int> indices2 = indices;
    indices.clear();

    for (int item : indices2) { // remove all items that got added to the
                                // threads
      if (!thread1.contains(item) && !thread2.contains(item))
        indices.push_back(item);
    }
  }
}

void solveFor1000(vector<int> indices) {
  while (indices.size() > 100) {
    int total1 = 0;
    int total2 = 1;
    unordered_set<int> subset1;
    unordered_set<int> subset2;

    while (total1 != total2) {
      total1 = 0;
      total2 = 0;
      subset1.clear();
      subset2.clear();
      for (int i = 0; i < indices.size(); ++i) {
        if (rand() % 2) { // v2 in the range 1 to 1000
          subset1.insert(indices[i]);
          total1 += stringLengths[indices[i] - 1];
        }
      }
      for (int i = 0; i < indices.size(); ++i) {
        if (rand() % 2) { // v2 in the range 1 to 1000
          subset2.insert(indices[i]);
          total2 += stringLengths[indices[i] - 1];
        }
      }
    }

    vector<int> indices2 = indices;
    indices.clear();

    for (int item : indices2) {
      if (subset1.contains(item) &&
          !subset2.contains(item)) { // remove if in both
        thread1.insert(item);
      } else if (subset2.contains(item) &&
                 !subset1.contains(item)) { // remove if in both
        thread2.insert(item);
      } else { // unused; we need to consider it again.
        indices.push_back(item);
      }
    }
  }
  solveFor100(indices);
}

void solveFor200000(const vector<int> &indices) {
  unordered_map<int, int> seen;
  // Remove duplicates
  for (int i = 0; i < indices.size(); ++i) {
    if (!seen.contains(stringLengths[indices[i] - 1])) {
      seen.emplace(stringLengths[indices[i] - 1], indices[i]);
    } else { // seen already
      thread1.insert(indices[i]);
      thread2.insert(seen[stringLengths[indices[i] - 1]]);
      seen.erase(stringLengths[indices[i] - 1]); // need 2 more for duplicate.
    }
  }
  OST indices3;

  for (auto [value, unmatched] : seen) {
    indices3.insert(unmatched);
  }

  // CAN REFACTOR.

  vector<int> pairs;
  unordered_map<int, pair<int, int>> sumSeen;

  for (int spacing = 1; spacing < N; spacing++) {
    for (int a = 0; a + spacing < indices3.size(); a++) {
      int summ = stringLengths[*indices3.find_by_order(a) - 1] +
                 stringLengths[*indices3.find_by_order(a + spacing) - 1];
      if (!sumSeen.contains(summ)) {
        sumSeen.emplace(
            summ, make_pair(*indices3.find_by_order(a),
                            *indices3.find_by_order(
                                a + spacing))); // track for later comparison
      } else {
        auto [c, d] = sumSeen[summ];
        if (indices3.find(c) == indices3.end() ||
            indices3.find(d) == indices3.end()) { // one has been deleted
          sumSeen[summ] =
              make_pair(*indices3.find_by_order(a),
                        *indices3.find_by_order(
                            a + spacing)); // track for later comparison

        } else {
          int b = *indices3.find_by_order(a + spacing);
          int a1 = *indices3.find_by_order(a);

          indices3.erase(a1);
          indices3.erase(b);
          indices3.erase(c);
          indices3.erase(d);

          thread1.insert(a1);
          thread1.insert(b);
          thread2.insert(c);
          thread2.insert(d);

          // Correct for removal to avoid skipping values
          a--; // removed a so when we advance a we don't actually want to
               // advance the index.
          if (c < a1) // c comes before a
            a--;      // indices are shifted back
          if (d < a1) // d comes before a
            a--;      // indices are shifted back

          sumSeen.erase(summ); // Already found a pair; don't want to add to
                               // thread again if 3.
        }
      } // already seen so remove
    }
  }
  vector<int> result = vector<int>(indices3.begin(), indices3.end());
  solveFor1000(result);
}

int main() {
  srand(1); // debug
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; ++t) {
    scanf("%d %d", &N, &K);
    stringLengths.assign(N, 0);
    for (int n = 0; n < N; ++n) {
      scanf("%d", &stringLengths[n]);
    }

    thread1.clear();
    thread2.clear();
    bool possible = false;
    vector<int> indices;
    for (int i = 1; i <= N; ++i)
      indices.push_back(i);

    //  solveFor200000(indices);

    if (N <= 25) {
      possible = solveFor25(indices);
    } else if (N <= 100) {
      possible = true;
      solveFor100(indices);
    } else if (N <= 1000) {
      possible = true;
      solveFor1000(indices);
    } else {
      possible = true;
      solveFor200000(indices);
    }

    if (possible) {
      printf("Case #%d: Possible\n", t);
      int iterNo = 0;
      auto it = thread1.begin();
      for (it = thread1.begin(); iterNo < thread1.size() - 1; ++it) {
        printf("%d ", *it);
        iterNo++;
      }
      printf("%d\n", *it);

      iterNo = 0;
      for (it = thread2.begin(); iterNo < thread2.size() - 1; ++it) {
        printf("%d ", *it);
        iterNo++;
      }
      printf("%d\n", *it);

    } else {
      printf("Case #%d: Impossible\n", t);
    }
    //  printf("Call Count %d\n",callCount);
  }
  return 0;
}
