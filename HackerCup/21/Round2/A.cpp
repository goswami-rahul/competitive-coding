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
  int n, m; cin >> n >> m;
  vector<vector<int>> a(n + 1, vector<int>(m));
  for (auto &s : a) for (int &x : s) cin >> x;
  int ans = 0;
  map<int,int> two, one;
  for (int x : a[0]) ++two[x];
  for (int i = 1; i <= n; ++i) {
    map<int,int> ntwo, none;
    vector<int> done(m);
    for (int j = 0; j < m; ++j) if (!done[j]) {
      int x = a[i][j];
      if (one.count(x) && one[x] > 0) {
        --one[x];
        ++none[x];
        done[j] = 1;
      }
    }
    for (int j = 0; j < m; ++j) if (!done[j]) {
      int x = a[i][j];
      if (two.count(x) && two[x] > 0) {
        --two[x];
        ++ntwo[x];
        done[j] = 1;
      }
    }
    for (int j = 0; j < m; ++j) if (!done[j]) {
      int x = a[i][j];
      ++none[x];
      int ok = 0;
      while (!two.empty()) {
        auto it = two.begin();
        if (it->second > 0) {
          ok = 1;
          it->second -= 1;
          break;
        } else {
          it = two.erase(it);
        }
      }
      if (!ok) ++ans;
    }
    swap(two, ntwo);
    swap(one, none);
  }
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