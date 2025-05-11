#include <bits/stdc++.h>

int main() {
  int tt; std::cin >> tt;
  while (tt--) {
    int n, m; std::cin >> n >> m;
    if (n > m) std::swap(n, m);
    if ((n + m) % 3 == 0 && n * 2 >= m) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}