#include <algorithm>
#include <iostream>
int n, m, x, y, sz;
static int days[400000], ans[200000], r[200000], b[400000];
static bool ext[400000];
bool cmp(int i, int j) {
  if (days[i] == days[j]) return ext[i] < ext[j];
  return days[i] < days[j];
}
int main() {
 
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
 
  scanf(" %d", &n);
  for (int i = 0; i < n; ++i) {
    scanf(" %d %d", &x, &y);
    days[i + i] = x;
    days[i + i + 1] = y;
    ext[i + i] = 0;
    ext[i + i + 1] = 1;
    b[i + i] = i + i;
    b[i + i + 1] = i + i + 1;
  }
  std::sort(b, b + n + n, cmp);
  for (int p = 0; p < n + n; ++p) {
    int i = b[p];
    if (ext[i]) {
      r[m++] = ans[i >> 1];
    } else {
      if (m == 0) {
        ans[i >> 1] = ++sz;
      } else {
        ans[i >> 1] = r[--m];
      }
    }
  }
  printf("%d\n", sz);
  for (int i = 0; i < n; ++i)
    printf("%d ", ans[i]);
  
  return 0;
}
