#ifdef Rahul
# include "RAHUL.h"
#else
# include <bits/stdc++.h>
  using namespace std;
# define error(...) 42;
#endif
#define SZ(v) int((v).size())
#define ALL(vec) begin(vec), end(vec)
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
#define Luv(...) [&] (auto &&u, auto &&v) { return __VA_ARGS__; }
using i64 = int64_t;
const int MOD = (int) 1e9 + 7;
const i64 INF = (i64) 1e18 + 42;

void SolveCase() {
  int n; cin >> n;
  double mn = 0, mx = INF;
  for (int x = 1; x <= n; ++x) {
    int a, b; cin >> a >> b;
    if (a > 0) uin(mx, (double) x / a);
    uax(mn, (double) x / b);
  }
  if (mn > mx) mn = -1;
  cout << fixed << setprecision(6) << mn << '\n';
}

int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    // cout << "Case #" << t << ": " << (SolveCase() ? "YES\n" : "NO\n");
    cout << "Case #" << t << ": "; SolveCase();   
  }
}
