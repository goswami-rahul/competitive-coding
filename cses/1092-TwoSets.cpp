#include <bits/stdc++.h>

int32_t main() {
  int n; std::cin >> n;
  if (n % 4 && (n + 1) % 4) {
    std::cout << "NO\n";
    return 0;
  }
  std::cout << "YES\n";
  int k = (n + 3) / 4, p = n | 1;
  std::set<int> s;
  for (int i = 1; i <= k; ++i) {
    s.insert(i);
    s.insert(p - i);
  }
  std::cout << s.size() << '\n';
  for (auto i : s) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
  std::cout << n - s.size() << '\n';
  for (int i = 1; i <= n; ++i) {
    if (!s.contains(i)) {
      std::cout << i << ' ';
    }
  }
  std::cout << '\n';
  return 0;
}