#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<pair<int, int>> a(n);
  for (auto &[x, y] : a) {
    cin >> y >> x;
  }
  sort(a.begin(), a.end());
  multiset<int> s;
  for (int i = 0; i < k; ++i) s.insert(-1);
  for (auto [r, l] : a) {
    auto it = s.upper_bound(l);
    if (it != s.begin()) {
      --it;
      s.erase(it);
      s.insert(r);
    } else {
      --n;
    }
  }
  cout << n;
}
