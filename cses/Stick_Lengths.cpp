#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  sort(a.begin(), a.end());
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += abs(a[i] - a[n / 2]);
  }
  cout << ans << "\n";
}
