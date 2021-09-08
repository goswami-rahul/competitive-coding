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

const int N = 51;
vector<int> path[N][N];
vector<int> g[N];
int s[N][N];
int a[N];
bool used[N];
bool edge[N][N];
int n, k;

void Init() {
  for (int i = 0; i < N; ++i) {
    g[i].clear();
    used[i] = 0;
    for (int j = 0; j < N; ++j) {
      path[i][j].clear();
      s[i][j] = 0;
      edge[i][j] = 0;
    }
  }
}

void Read() {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n - 1; ++i) {
    int u, v; cin >> u >> v; --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
    edge[u][v] = edge[v][u] = 1;
  }
}

void Dfs(int u, int p, vector<int> &nodes) {
  nodes.push_back(u);
  bool leaf = true;
  for (int v : g[u]) if (v != p) {
    Dfs(v, u, nodes);
    leaf = false;
  }
  if (leaf) path[nodes[0]][u] = nodes;
  nodes.pop_back();
}

int SolveCase() {
  Init(), Read();
  if (k == 0) return a[0];
  if (k >= n - 2) return accumulate(a, a + n, 0);
  vector<int> nodes;
  Dfs(0, -1, nodes);
  vector<int> leafs;
  for (int i = 1; i < n; ++i) {
    if (!path[0][i].empty()) {
      leafs.push_back(i);
    }
  }

  return -1;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 