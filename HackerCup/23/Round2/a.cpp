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

const int N = 3005;
int v[N][N];
int e[N * N];
int z[N * N];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int SolveCase() {
  int n, m; cin >> n >> m;
  vector<string> a(n);
  for (string &s : a) cin >> s;
  int t = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      v[i][j] = z[i * m + j] = 0;
      e[i * m + j] = -42;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (a[i][j] == 'W') {
      if (v[i][j]) continue;
      ++t;
      vector<pair<int, int>> bfs = {{i, j}};
      v[i][j] = t;
      for (int k = 0; k < bfs.size(); ++k) {
        auto [x, y] = bfs[k];
        for (int l = 0; l < 4; ++l) {
          int o = x + dx[l], p = y + dy[l];
          if (o < n && o >= 0 && p < m && p >= 0 && v[o][p] == 0) {
            if (a[o][p] == 'W') {
              v[o][p] = t;
              bfs.emplace_back(o, p);
            }
            if (a[o][p] == '.') {
              if (e[t] == -42 || e[t] == o * m + p) {
                e[t] = o * m + p;
              } else {
                e[t] = -1;
              }
            }
          }
        }
      }
      z[t] = bfs.size();
    }
  }
  map<int, int> r;
  for (int g = 1; g <= t; ++g) if (e[g] >= 0) {
    r[e[g]] += z[g];
    // error(g, e[g]/m, e[g]%m, z[g], a[e[g]/m][e[g]%m])
  }
  int ans = 0;
  for (auto [key, value] : r) uax(ans, value);
  return ans;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << (SolveCase() > 0 ? "YES" : "NO") << '\n';
  }
} 