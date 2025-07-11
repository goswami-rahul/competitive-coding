#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, l, r; cin >> n >> l >> r;
  multiset<long long> m = {(long long)2e18};
  vector<long long> a(n + 1);
  long long ans = -2e18;
  for (int i = 1, j = 0, k = 0; i <= n; ++i) {
    cin >> a[i];
    a[i] += a[i - 1];
    while (j <= i - l) m.insert(a[j++]);
    while (k < i - r) m.extract(a[k++]);
    ans = max(ans, a[i] - *m.begin());
  }
  cout << ans;
}
