#include <bits/stdc++.h>
int main() {
  long long a = 1, b = 2, m = 1e9+7, n;
  for (std::cin >> n; n; n >>= 1) {
    if (n & 1) (a *= b) %= m;
    (b *= b) %= m;
  }
  std::cout << a;
}
