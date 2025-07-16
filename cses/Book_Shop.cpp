#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, t; cin >> n >> t;
  vector<int> h(n), s(n);
  for (int &x : h) cin >> x;
  for (int &x : s) cin >> x;
  vector<int> a(t + 1);
  for (int i = 0; i < n; ++i) {
    for (int j = t; j >= h[i]; --j) {
      a[j] = max(a[j], a[j - h[i]] + s[i]);
    }
  }
  cout << a[t];
}
