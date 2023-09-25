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

int Calc(array<int, 4> a, array<int, 4> b) {
  int sa = a[1] + a[2] * 2 + a[3] * 3;
  int sb = b[1] + b[2] * 2 + b[3] * 3;
  if (sa > sb) swap(a, b), swap(sa, sb);
  int d = sb - sa;
  if (d % 2) return -1;
  d /= 2;
  int m = min({a[1], b[3], d / 2});
  int ans = m;
  d -= m * 2;
  a[1] -= m, a[3] += m;
  b[3] -= m, b[1] += m;
  m = min({a[1], b[2], d});
  ans += m;
  d -= m;
  a[1] -= m, a[2] += m;
  b[2] -= m, b[1] += m;
  m = min({a[2], b[3], d});
  ans += m;
  d -= m;
  if (d > 0) return -1;
  return ans;
}

int SolveCase() {
  int total = 0;
  int n, m; cin >> n >> m;
  vector<array<int, 4>> bit(n + 5, array<int, 4>{});
  array<int, 4> cnt{};
  auto Add = [&] (int i, int v, int c) {
    for (i += 2; i < n + 5; i += i & -i) {
      bit[i][v] += c;
    }
    cnt[v] += c;
  };
  auto Get = [&] (int i) {
    array<int, 4> r{};
    for (i += 2; i > 0; i -= i & -i) {
      for (int j = 1; j <= 3; ++j) r[j] += bit[i][j];
    }
    return r;
  };
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    Add(i, a[i], 1);
  }
  while (m--) {
    int i, v, p; cin >> i >> v >> p;
    Add(i, a[i], -1);
    a[i] = v;
    Add(i, a[i], +1);
    auto lf = Get(p);
    array<int, 4> rg;
    for (int j = 1; j <= 3; ++j) rg[j] = cnt[j] - lf[j];
    total += Calc(lf, rg);
  }
  return total;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 