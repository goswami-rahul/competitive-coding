#include <bits/stdc++.h> 
int a[1001];
std::unordered_map<int,std::vector<std::pair<int,int>>> M;
int n, x;
int main() {
  scanf("%d %d", &n, &x);
  for (int i = 1; i <= n; ++i) { 
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < i; ++j) if (a[i] + a[j] + 1 < x && M.count(x - a[i] - a[j])) {
      const auto& vec = M[x - a[i] - a[j]];
      for (auto it = vec.begin(); it != vec.end(); ) {
        if (it->first == j) {
          it = upper_bound(it, vec.end(), std::pair<int,int>{j, 10000000});
        } else if (it->second == j) {
          ++it;
        } else {
          return !printf("%d %d %d %d", i, j, it->first, it->second);
        }
      }
    }
    for (int j = 1; j < i; ++j) if (a[i] + a[j] < x) {
      M[a[i] + a[j]].emplace_back(i, j);
    }
  }
  puts("IMPOSSIBLE");
}
