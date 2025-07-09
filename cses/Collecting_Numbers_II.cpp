#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, m; 
  cin >> n >> m;
  vector<int> a(n + 2);
  vector<int> b(n + 2);
  a[n + 1] = n + 1;
  b[n + 1] = n + 1;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    a[x] = i;
    b[i] = x;
  }
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i] < a[i - 1]) {
      ans++;
    }
  }
  while (m--) {
    int i, j; cin >> i >> j;
    swap(b[i], b[j]);
    i = b[i], j = b[j];
    if (i > j) swap(i, j);
    ans -= a[i] < a[i - 1];
    ans -= a[j] < a[j - 1];
    if (j - 1 > i) ans -= a[i + 1] < a[i];
    ans -= a[j + 1] < a[j];
    swap(a[i], a[j]);
    ans += a[i] < a[i - 1];
    ans += a[j] < a[j - 1];
    if (j - 1 > i) ans += a[i + 1] < a[i];
    ans += a[j + 1] < a[j];
    cout << ans << "\n";
  }
}
