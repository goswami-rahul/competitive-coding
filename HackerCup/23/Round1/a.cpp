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

double SolveCase() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  sort(ALL(a));
  if (n != 5) {
    return (a[n-1] + a[n-2]) / (double) 2.0 - (a[0] + a[1]) / (double) 2.0;
  }
  return max((a[2] + a[4]) / (double) 2.0 - (a[0] + a[1]) / (double) 2.0, 
             (a[3] + a[4]) / (double) 2.0 - (a[0] + a[2]) / (double) 2.0);
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << fixed << setprecision(2) << SolveCase() << '\n';
  }
} 