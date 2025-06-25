#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h> 
int n, a[20];
long long go(int i, long long s, long long t) {
  if (i == n) return (s < t ? t - s : s - t);
  return std::min(go(i + 1, s + a[i], t), go(i + 1, s, t + a[i]));
}
int main() {
  scanf("%d", &n);
  printf("%lld\n", go(0, 0, 0));
}
