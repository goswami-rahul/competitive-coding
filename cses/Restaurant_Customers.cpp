#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<pair<int, int>> a;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    a.emplace_back(x, +1);
    a.emplace_back(y, -1);
  }
  sort(a.begin(), a.end());
  int ans = 0, sum = 0;
  for (auto [x, y] : a) {
    sum += y;
    ans = max(ans, sum); 
  }
  cout << ans << '\n';
}
