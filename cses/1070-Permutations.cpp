#include <bits/stdc++.h>
int32_t main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  scanf("%d", &n);
  if (n == 2 || n == 3) puts("NO SOLUTION");
  else for (int i = 0; i < n; ++i) printf("%d ", (i & 1) ? (i + 1) >> 1 : (n >> 1) + (i >> 1) + 1);
  return 0;
}
