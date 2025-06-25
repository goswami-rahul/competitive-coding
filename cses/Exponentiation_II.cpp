#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <stdio.h> 
static int a, b, c, ans, n;
static const int mod = 1e9 + 7, nod = mod - 1;
int main() {
  for (scanf("%d", &n); n--; ) {
    scanf("%d %d %d", &a, &b, &c);
    for (ans = 1; c; c >>= 1, b = 1LL * b * b % nod) {
      if (c & 1) ans = 1LL * ans * b % nod;
    }
    for (b = ans, ans = 1; b; b >>= 1, a = 1LL * a * a % mod)
      if (b & 1) ans = 1LL * ans * a % mod;
    printf("%d\n", ans);
  }
}
