#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    a[x - 1] = i;
  }
  int ans = 1;
  for (int i = 1; i < n; i++) {
    if (a[i] < a[i - 1]) {
      ans++;
    }
  }
  cout << ans << "\n";
}
