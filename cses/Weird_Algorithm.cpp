#include <bits/stdc++.h>
int main() {
  long long n; scanf(" %lld", &n);
  while (n > 1) {
    printf("%lld ", n);
    if (n & 1) n = 3 * n + 1;
    else n >>= 1;
  }
  printf("1\n");
}
