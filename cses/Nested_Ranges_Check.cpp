#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<tuple<int,int,int>> a(n);
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    a[i] = {x, -y, i};
  }
  sort(a.rbegin(), a.rend());
  vector<int> ans(n);
  int mr = 2e9;
  for (auto [l, r, i] : a) {
    r = -r;
    ans[i] = mr <= r;
    mr = min(mr, r);
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  reverse(a.begin(), a.end());
  mr = -1;
  for (auto [l, r, i] : a) {
    r = -r;
    ans[i] = mr >= r;
    mr = max(mr, r);
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
}
