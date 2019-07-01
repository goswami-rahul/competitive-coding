#include <stdio.h> 
int n, a[1000001], x;
int main() {
  for (int i = 2; i <= 500000; ++i) 
    for (int j = i + i; j <= 1000000; j += i)
      ++a[j];
  a[1] = -1;
  for (scanf("%d", &n); n--; ) {
    scanf("%d", &x);
    printf("%d\n", a[x] + 2);
  }
}
