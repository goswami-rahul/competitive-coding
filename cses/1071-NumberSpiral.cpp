#include<bits/stdc++.h>

int main() {
  int tt; 
  scanf("%d", &tt);
  while (tt--) {
    int x, y;
    scanf("%d %d", &x, &y);
    int m = x > y ? x : y;
    --m;
    long long ans = (long long) m * m;
    if (m & 1) {
      std::swap(x, y);
    }
    if (x == m + 1) {
      ans += y;
    } else {
      ans += m + 1 + m + 1 - x;
    }
    printf("%lld\n", ans);
  }
}