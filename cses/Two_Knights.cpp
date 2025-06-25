#include <bits/stdc++.h>

int32_t main() {
  std::cin.tie(nullptr) -> sync_with_stdio(false);
  int64_t n; std::cin >> n;
  int64_t ans = 0;
  for (int64_t i = 1; i <= n; ++i) {
    if (i >= 3) {
      ans += (i - 2) * 2 * 2;
      ans += 4;
    }
    if (i >= 4) {
      ans += 4;
    }
    if (i >= 5) {
      ans += (i - 4) * 2 * 2;
    }
    std::cout << i * i * (i * i - 1) / 2 - ans << '\n';
  }
}