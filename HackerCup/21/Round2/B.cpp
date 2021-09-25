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

const int N = 8e5 + 42, LN = 20;
vector<int> g[N];
int ent[N];
int ext[N];
int dep[N];
int par[LN][N];
int up[N];

int Lca(int u, int v) {
  if (u == v) return u;
  if (ent[u] > ent[v]) swap(u, v);
  if (ent[u] < ent[v] && ext[v] < ext[u]) return u;
  for (int i = LN - 1; ~i; --i) {
    if (ent[par[i][u]] < ent[v] && ext[v] < ext[par[i][u]]) continue;
    u = par[i][u];
  }
  return par[0][u];
}
void Dfs(int u = 0, int p = 0) {
  static int tick = 0;
  par[0][u] = p;
  for (int i = 1; i < LN; ++i)
    par[i][u] = par[i - 1][par[i - 1][u]];
  ent[u] = tick++;
  for (int v : g[u]) if (v != p) {
    dep[v] = 1 + dep[u];
    Dfs(v, u);
  }
  ext[u] = tick++;
}

void ReadGraph(int n) {
  for (int i = 0; i < n; ++i) g[i].clear(), dep[i] = 0, up[i] = MOD;
  for (int i = 0; i < n - 1; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
} 

int Solve(int u = 0, int p = 0) {
  int res = 0;
  for (int v : g[u]) if (v != p) {
    res += Solve(v, u);
    res += dep[u] < up[v];
    uin(up[u], up[v]);
  }
  return res;
}

void SolveCase() {
  int n; cin >> n;
  ReadGraph(n);
  Dfs();
  vector<vector<int>> fs(n);
  for (int i = 0; i < n; ++i) {
    int f; cin >> f, --f;
    fs[f].push_back(i);
  }
  for (auto &f : fs) if (!f.empty()) {
    sort(ALL(f), Luv(ent[u] < ent[v]));
    int lca = f[0];
    for (int u : f) lca = Lca(u, lca);
    for (int u : f) up[u] = dep[lca];
  }
  cout << Solve() << '\n';
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    SolveCase();
  }
} 