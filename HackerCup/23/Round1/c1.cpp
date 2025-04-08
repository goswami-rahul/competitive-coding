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
  int n; cin >> n;
  string s; cin >> s;
  vector<int> t(n + 1, 0);
  int q; cin >> q;
  while (q--) {
    int b; cin >> b;
    t[b] ^= 1;
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (s[i-1] == '0') {
      ans += t[i];
    } else {
      ans += t[i] == 0;
      for (int j = i; j <= n; j += i) {
        s[j-1] ^= '0' ^ '1';
      }
    }
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