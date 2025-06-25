#include <bits/stdc++.h> 
static int a[101];
static std::bitset<2000002> lose;
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < k; ++i) 
    scanf("%d", a + i);
  n += 1000000;
  lose[1000000] = 1;
  for (int i = 1000001; i <= n; ++i) {
    for (int j = 0; j < k; ++j) {
      lose[i] = 1;
      if (lose[i - a[j]]) {
        lose[i] = 0; break;
      }
    }
    putchar_unlocked(lose[i] ? 'L' : 'W');
  }  
  
}
