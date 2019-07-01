#include <stdio.h>
int main() {
  int n;
  scanf(" %d", &n);
  long long a = (long long) n * (n + 1) / 2;
  while (n-- > 1) {
    int x;
    scanf(" %d", &x);
    a -= x;
  }
  printf("%lld", a);
}
