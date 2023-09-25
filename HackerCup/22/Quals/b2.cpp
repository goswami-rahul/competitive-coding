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

const int N = 3010;
char a[N][N];
int deg[N][N];

int n, m;

void Print() {
  cout << "Possible\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << a[i][j];
    }
    cout << '\n';
  }
}

void SolveCase() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
      deg[i][j] = 0;
    }
  }
  std::set<tuple<int, int, int>> s;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (a[i][j] != '#') {
      if (i > 0 && a[i - 1][j] != '#') ++deg[i][j];
      if (i < n - 1 && a[i + 1][j] != '#') ++deg[i][j];
      if (j < m - 1 && a[i][j + 1] != '#') ++deg[i][j];
      if (j > 0 && a[i][j - 1] != '#') ++deg[i][j];
      s.emplace(deg[i][j], i, j);
    }
  }
  auto Sub = [&s] (int i, int j) {
    if (a[i][j] == '^' || a[i][j] == '.') {
      s.erase({deg[i][j], i, j});
      --deg[i][j];
      s.insert({deg[i][j], i, j});
    }
  };
  while (!s.empty()) {
    auto it = s.begin();
    auto [d, i, j] = *it;
    if (d >= 2) break;
    if (a[i][j] == '^') {
      cout << "Impossible\n";
      return;
    }
    assert (a[i][j] == '.');
    s.erase({deg[i][j], i, j});
    a[i][j] = 'x';
    if (i > 0) Sub(i - 1, j);
    if (j > 0) Sub(i, j - 1);
    if (i < n - 1) Sub(i + 1, j);
    if (j < m - 1) Sub(i, j + 1);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == 'x') a[i][j] = '.';
      else if (a[i][j] == '.') a[i][j] = '^';
    }
  }
  Print();
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    SolveCase();
  }
} 