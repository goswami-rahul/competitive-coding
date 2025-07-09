#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, m, k; cin >> n >> m >> k;
  vector<int> a(n), b(m);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  int i = 0, j = 0, ans = 0;
  while (j < m) {
    while (i < n && a[i] < b[j] - k) i++;
    if (i < n && a[i] <= b[j] + k) {
      ans++;
      i++;
    }
    j++;
  }
  cout << ans << '\n';
}
