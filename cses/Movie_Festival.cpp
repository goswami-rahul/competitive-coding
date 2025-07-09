#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<pair<int, int>> a(n);
  for (auto &[x, y] : a) {
    cin >> x >> y;
  }
  sort(a.begin(), a.end());
  vector<int> dp(n, 1);
  for (int i = n - 2; i >= 0; --i) {
    dp[i] = dp[i + 1];
    int j = lower_bound(a.begin() + i, a.end(), pair{a[i].second, -1}) - a.begin();
    if (j < n) dp[i] = max(dp[i], dp[j] + 1);
  }
  cout << dp[0] << '\n';
}
