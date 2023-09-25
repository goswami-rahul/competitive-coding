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

i64 SolveCase() {
  i64 a, b, c; cin >> a >> b >> c;
  uin(a, b);
  vector<i64> cands = {c / a};
  if (c >= b) {
    cands.push_back(c / b * 2 - 1);
  }
  if (c >= a) {
    cands.push_back(1 + (c - a) / b * 2);
  }
  if (c >= 2 * a) {
    cands.push_back(2 + (c - 2 * a) / b * 2);
  }
  if (c >= 3 * a) {
    cands.push_back(3 + (c - 3 * a) / b * 2);
  }
  return *max_element(ALL(cands));
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 