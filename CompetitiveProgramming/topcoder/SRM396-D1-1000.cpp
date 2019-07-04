/**
 * We use Gaussian elimination to solve it.
 * From the given set of numbers, we want to remove some numbers
 * such that the remaining numbers dont have any subset with 0 xor, and 
 * sum of removes numbers is minimum.
 * this is equivalent to finding the set with all subsets having non-zero sums
 * and its sum is maximal.
 * For this we sort the numbers in descending order, and try to add them 
 * to the basis. If is not linearly independent from the current basis, ie
 * if it is possible to get xor equal to 0 with this number ^ basis, 
 * we dont add it to the basis, otherwise we add it to the basis.
**/
#include <bits/stdc++.h>
using namespace std;

class MoreNim {
  public:
  vector<long long> basis;
  bool add(long long x) {
    for (long long b: basis) x = min(x, x ^ b);
    if (x == 0) return false;
    basis.push_back(x);
    sort(basis.begin(), basis.end(), greater<long long>());
    return true;
  }
  long long bestSet(vector<string> heaps) {
    int n = (int) heaps.size();
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) a[i] = stoll(heaps[i]);
    sort(a.begin(), a.end(), greater<long long>());
    long long ans = 0;
    for (long long x: a) {
      if (!add(x)) ans += x;
    }
    return ans;
  }
};
