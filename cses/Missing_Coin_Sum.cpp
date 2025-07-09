#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  sort(a.begin(), a.end());
  long long ans = 1;
  for (int x : a) {
    if (ans < x) {
      cout << ans << "\n";
      return 0;
    }
    ans += x;
  }
  cout << ans << "\n";
}
