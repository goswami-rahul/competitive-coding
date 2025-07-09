#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  int j = 0;
  int ans = 1;
  multiset<int> s = {a[0]};
  for (int i = 1; i < n; i++) {
    while (s.contains(a[i])) {
      s.extract(a[j++]);
    }
    s.insert(a[i]);
    ans = max(ans, (int) s.size());
  }
  cout << ans << "\n";
}
