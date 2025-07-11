#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> m(n);
  ++m[0];
  long long sum = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    sum = (sum + x) % n;
    if (sum < 0) sum += n;
    ans += m[sum];
    ++m[sum];
  }
  cout << ans;
}
