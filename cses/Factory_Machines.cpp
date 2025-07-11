#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, t; cin >> n >> t;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  long long lo = 1, hi = 2e18;
  while (lo < hi) {
    long long md = (lo + hi) / 2;
    long long s = t;
    for (int x : a) {
      s -= md / x;
      if (s <= 0) break;
    }
    if (s <= 0) hi = md;
    else lo = md + 1;
  }
  cout << lo;
}
