#include<bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int x, n; cin >> x >> n;
  set<int> s = {0, x};
  multiset<int> m = {x};
  for (int k = 0; k < n; ++k) {
    int p; cin >> p;
    auto it = s.upper_bound(p);
    int i = *it, j = *prev(it);
    m.extract(i - j);
    m.insert(p - j);
    m.insert(i - p);
    s.insert(p);
    cout << *m.rbegin() << ' ';
  }
}
