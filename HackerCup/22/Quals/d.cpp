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
  int n, m, q; cin >> n >> m >> q;
  vector<vector<pair<int,int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w; cin >> u >> v >> w; --u, --v;
    g[u].emplace_back(w, v);
    g[v].emplace_back(w, u);
  }
  for (auto &e : g) sort(ALL(e), greater{});
  vector<map<int, int>> qs(n);
  vector<vector<int>> dups(q);
  vector<i64> ans(q, 0);
  for (int i = 0; i < q; ++i) {
    int x, y; cin >> x >> y; --x, --y;
    if (auto it = qs[x].find(y); it != qs[x].end()) {
      dups[it->second].push_back(i);
      continue;
    }
    qs[x][y] = i;
    qs[y][x] = i;
  }
  for (int p = 0; p < n; ++p) {
    const auto& e = g[p];
    std::set<int> seen;
    for (int i = 0; i < SZ(e); ++i) {
      auto [w, u] = e[i];
      seen.insert(u);
      if (auto it = qs[u].find(p); it != qs[u].end()) {
        ans[it->second] += w;
      }
      if (SZ(qs[u]) < i) {
        for (const auto& [v, z] : qs[u]) {
          if (seen.count(v)) {
            ans[z] += w;
          }
        }
      } else {
        for (int j = 0; j < i; ++j) {
          auto [_, v] = e[j];
          if (auto it = qs[u].find(v); it != qs[u].end()) {
            ans[it->second] += w;
          }
        }
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    for (int d : dups[i]) ans[d] = ans[i];
  }
  for (i64 x : ans) cout << x << ' ';
  cout << '\n';
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    error(t);
    SolveCase();
  }
} 