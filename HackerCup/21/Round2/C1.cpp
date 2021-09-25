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

int Solve(vector<vector<int>> a, int k) {
  int ans = 1e9, n = a.size(), m = a[0].size();
  for (int i = 1; i < 3 * n; ++i) {
    if (i >= a.size()) a.emplace_back(m, 0);
    if (i > k) {
      int cur = i - k;
      for (int j = 0; j < m; ++j) {
        cur += a[i][j] || a[i - 1][j] > k;
      }
      uin(ans, cur);
    }
    for (int j = 0; j < m; ++j) {
      a[i][j] += a[i - 1][j];
    }
  }
  return ans;
}

void SolveCase() {
  int r, c, k; cin >> r >> c >> k;
  --k;
  vector a(r, vector(c, 0));
  for (auto &row : a) {
    for (int &x : row) {
      char e; cin >> e;
      x = e == 'X';
    }
  }
  int ans = accumulate(ALL(a[k]), 0);
  uin(ans, Solve(a, k));
  reverse(ALL(a));
  uin(ans, Solve(a, r - 1 - k));
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    SolveCase();
  }
} 