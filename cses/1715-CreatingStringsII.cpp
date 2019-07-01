#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h> 
static long long num = 1, den = 1, mod = 1e9 + 7, cnt, a[256];
static char c;
int main() {
  while (scanf("%c", &c) != EOF) {
    if (c < 'a') break;
    ++cnt; ++a[c];
    (num *= cnt) %= mod;
    (den *= a[c]) %= mod;
  }
  for (cnt = mod - 2; cnt; cnt >>= 1) {
    if (cnt & 1) (num *= den) %= mod;
    (den *= den) %= mod;
  }
  printf("%d", num);
}
