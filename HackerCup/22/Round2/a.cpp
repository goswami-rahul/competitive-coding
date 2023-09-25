#ifdef Rahul
#include "RAHUL.h"
#else
#include <bits/stdc++.h>
using namespace std;
#define error(...) 42;
#endif
#define SZ(v) int((v).size())
#define ALL(vec) begin(vec), end(vec)
using i64 = int64_t;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
#define Luv(...) [&] (auto &&u, auto &&v) { return __VA_ARGS__; }
const int MOD = (int) 1e9 + 7;
const i64 INF = (i64) 1e18 + 42;

const int K = 26;

bool Ok(const auto& s, const auto& b) {
  int diff = 0;
  for (int i = 0; i < K; ++i) {
    if (s[i] == b[i]) continue;
    ++diff;
    if (abs(s[i] - b[i]) != 1) return false;
  }
  return diff == 1;
}
int SolveCase() {
  string s; cin >> s;
  int n = SZ(s);
  vector<array<int, K>> a(n + 1, array<int, K>{});
  for (int i = 1; i <= n; ++i) {
    a[i] = a[i - 1];
    a[i][s[i - 1] - 'a']++;
  }
  int ans = 0, q;
  cin >> q;
  while (q--) {
    int l, r; cin >> l >> r; --l;
    if ((r - l) % 2 == 0) continue;
    array<int, K> x, y;
    int m = l + (r - l) / 2;
    for (int i = 0; i < K; ++i) {
      x[i] = a[r][i] - a[m][i];
      y[i] = a[m][i] - a[l][i];
    }
    if (Ok(x, y)) {
      ++ans;
      continue;
    }
    m = l + (r - l) / 2 + 1;
    for (int i = 0; i < K; ++i) {
      x[i] = a[r][i] - a[m][i];
      y[i] = a[m][i] - a[l][i];
    }
    ans += Ok(x, y);
  }
  return ans;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 