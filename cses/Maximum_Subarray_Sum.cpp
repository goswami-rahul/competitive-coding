#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  long long sum = 0, ans = -4e18;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    sum += x;
    ans = max(ans, sum);
    sum = max(sum, 0LL);
  }
  cout << ans << "\n";
}
