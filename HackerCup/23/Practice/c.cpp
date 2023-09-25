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

bool Ok(vector<i64> a, i64 p) {
  if (p <= 0) return false;
  a.push_back(p);
  sort(ALL(a));
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] + a[a.size() - 1 - i] != a.front() + a.back()) {
      return false;
    }
  }
  return true;
}

int SolveCase() {
  int n; cin >> n;
  vector<i64> a(2 * n - 1);
  for (i64 &x : a) cin >> x;
  if (n == 1) return 1;
  sort(ALL(a));
  i64 s = accumulate(ALL(a), 0LL);
  for (i64 t : {a[0] + a[2 * n - 3], a[0] + a[2 * n - 2], a[1] + a[2 * n - 2]}) {
    if (Ok(a, t * n - s)) return t * n - s;
  }
  return -1;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 