#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  long long ans = 0;
  map<int, int> s;
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];
    while (s.size() > k) {
      int x = a[j++];
      if (--s[x] == 0) s.erase(x);
    }
    ans += i - j + 1;
  }
  cout << ans << "\n";
}
