#include <bits/stdc++.h>
using namespace std;
static int cnt[1000001];
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n; scanf(" %d", &n);
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    int x; scanf(" %d", &x); cnt[x]++; if (x > mx) mx = x;
  }
  for (int i = mx; i > 1; --i) {
    int k = 0;
    for (int j = i; j <= mx; j += i) {
      k += cnt[j];
      if (k > 1) return !printf("%d", i);
    }
  }
  puts("1");
  return 0;
}
