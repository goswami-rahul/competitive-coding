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

void SolveCase() {
  int n; cin >> n;
  vector<int> rowd(n), cold(n), rowo(n), colo(n);
  vector<pair<int,int>> dots;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c; cin >> c;
      rowd[i] += c == '.';
      cold[j] += c == '.';
      rowo[i] += c == 'O';
      colo[j] += c == 'O';
      if (c == '.') dots.emplace_back(i, j);
    }
  }
  int ans = MOD, cnt = -1;
  for (int i = 0; i < n; ++i) {
    if (rowo[i] == 0) {
      if (uin(ans, rowd[i])) cnt = 0;
      cnt += ans == rowd[i];
    }
    if (colo[i] == 0) {
      if (uin(ans, cold[i])) cnt = 0;
      cnt += ans == cold[i];
    }
  }
  for (auto [x, y] : dots) {
    cnt -= rowo[x] == 0 && rowd[x] == 1 && colo[y] == 0 && cold[y] == 1;
  }
  if (cnt == -1) cout << "Impossible\n";
  else cout << ans << ' ' << cnt << '\n';
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    SolveCase();
  }
} 