#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, x; cin >> n >> x;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    int y; cin >> y;
    a[i] = {y, i + 1};
  }
  sort(a.begin(), a.end());
  for (int i = 1; i < n; i++) {
    auto j = lower_bound(a.begin(), a.begin() + i, pair{x - a[i].first, -1}) - a.begin();
    if (j < i && a[j].first + a[i].first == x) {
      cout << a[i].second << " " << a[j].second << "\n";
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
  return 0;
}
