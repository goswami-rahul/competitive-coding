#include <stdio.h>
int main() {
  int n, now = 0;
  long long ans = 0;
  scanf("%d", &n);
  while (n--) {
    int x;
    scanf("%d", &x);
    if (x > now) now = x;
    ans += now - x;
  }
  printf("%lld", ans);
}
