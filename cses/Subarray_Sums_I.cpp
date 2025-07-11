#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int s; cin >> s;
  map<long long, int> m;
  ++m[0];
  long long sum = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    sum += x;
    ans += m[sum - s];
    ++m[sum];
  }
  cout << ans;
}
