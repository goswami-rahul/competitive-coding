#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, t; cin >> n >> t;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  long long lo = 1, hi = 2e18;
  while (lo < hi) {
    long long md = (lo + hi) / 2;
    long long s = 1, sum = 0;
    for (int x : a) {
      if (x > md) s = 2e9;
      if (sum + x > md) {
        sum = 0;
        ++s;
      } 
      sum += x;
    }
    if (s <= t) hi = md;
    else lo = md + 1;
  }
  cout << lo;
}
