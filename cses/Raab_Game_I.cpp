#include<bits/stdc++.h>
using namespace std;

int main() {
  int tt; cin >> tt;
  while (tt--) {
    int n, a, b; cin >> n >> a >> b;
    if (a + b > n || a == 0 || b == 0) {
      if (a > 0 || b > 0) {
        cout << "NO\n";
        continue;
      }
    }
    cout << "YES\n";
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    int i = 0;
    while (a + b + i < n) ++i;
    while (a > 1 && b > 1) {
      swap(p[i], p[i + 1]);
      i += 2;
      --a, --b;
    }
    rotate(p.begin() + i, p.begin() + i + b, p.end());
    for (int i = 0; i < n; ++i) {
      cout << p[i] + 1 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
      cout << i + 1 << ' ';
    }
    cout << '\n';
  }
}
