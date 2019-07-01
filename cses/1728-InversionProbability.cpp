#include <bits/stdc++.h> 
int a[101];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) 
    scanf("%d", a + i);
  double ans = 0, sum;
  for (int i = n - 1; i >= 0; --i) {
    sum = 0;
    for (int j = 1; j < a[i]; ++j) {
      for (int k = i + 1; k < n; ++k) {
        sum += 1. * std::min(j, a[k]) / a[k];
      }
    }
    ans += sum / a[i];
  }
  printf("%.6f", ans);
}
