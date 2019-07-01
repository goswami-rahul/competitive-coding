/**
 *    author:  tourist
 *    created: 31.03.2018 11:41:48       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i];
    }
    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int dx = x[i] - x[j];
        int dy = y[j] - y[i];
        if (dx > 0 && dy > 0) {
          int g = __gcd(dx, dy);
          dx /= g;
          dy /= g;
          s.emplace(dx, dy);
        }
      }
    }
    cout << (int) s.size() + 1 << '\n';
  }
  return 0;
}
