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

int SolveCase() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v; cin >> u >> v; --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  auto Dfs = [&](int u, int p, const auto& f) -> int {
    vector<int> b;
    for (int v : g[u]) if (v != p) {
      b.push_back(f(v, u, f));
    }
    if (b.empty()) return a[u];
    if (u == 0) {
      sort(ALL(b), greater{});
      return a[u] + b[0] + (b.size() > 1 ? b[1] : 0);
    }
    return *max_element(ALL(b)) + a[u];
  };
  return Dfs(0, -1, Dfs);
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 