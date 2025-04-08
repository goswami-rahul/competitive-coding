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

const int M = 1e7 + 42;
int sols[M];
int lpf[M];

void RunPrimes() {
  for (int i = 1; i < M; ++i) lpf[i] = i;
  for (int i = 2; i < M; ++i) {
    if (lpf[i] == i) {
      for (int j = i + i; j < M; j += i) {
        if (lpf[j] == j) lpf[j] = i;
      }
    }
  }
  sols[5] = 2;
  for (int i = 6; i < M; ++i) {
    sols[i] = sols[i-1] + (lpf[i] == i && lpf[i-2] == i-2);
  }
}

int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  RunPrimes();
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    int n; cin >> n;
    cout << "Case #" << t << ": " << sols[n] << '\n';   
  }
}
