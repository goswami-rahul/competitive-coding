#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  long long ans = 0;
  multiset<int> s;
  for (int i = 0, j = 0; i < n; ++i) {
    while (s.contains(a[i])) {
      s.extract(a[j++]);
    }
    s.insert(a[i]);
    ans += s.size();
  }
  cout << ans << "\n";
}
