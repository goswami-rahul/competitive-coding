#include <bits/stdc++.h>
#define l long long
l m = 1e9 + 7, n;
std::map<l,l> M;
l f(l n) {
  if (n < 3) return !!n;
  if (M.count(n)) return M[n];
  l k = (n + 1) / 2, a = f(k - 1), b = f(k);
  return M[n] = (n & 1 ? a * a + b * b : (2 * a + b) * b) % m;
}
main() {
  std::cin >> n; std::cout << f(n);
}
