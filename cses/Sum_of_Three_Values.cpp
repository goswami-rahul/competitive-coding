#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, x; cin >> n >> x;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  map<int, int> s;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (s.count(x - a[i] - a[j])) {
        cout << i + 1 << ' ' <<  j + 1 << ' ' << s[x - a[i] - a[j]];
        return 0;
      }
    }
    s[a[i]] = i + 1;
  }
  cout << "IMPOSSIBLE";
}
