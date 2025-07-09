#include<bits/stdc++.h>
using namespace std;

int main() {
  const int md = 1e9 + 7;
  int n; cin >> n;
  map<int, int> cnt;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ++cnt[x];
  }
  long long ans = 1;
  for (auto [_, c] : cnt) {
    ans = (ans * (c + 1)) % md;
  }
  cout << ans - 1;
}
