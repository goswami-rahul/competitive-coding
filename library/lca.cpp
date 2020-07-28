template<class Monoid, int InNodes = 0>
class LCA {
  using T = typename Monoid::type;
  struct Edge {
    int to;
    T cost;
  };
  bool is_build;
  const int size;
  int log_size, root;
  vector<vector<int>> parent;
  vector<vector<T>> dp;
  vector<int> depth;
  vector<vector<Edge>> G;
  void dfs(int v, int pv) {
    parent[0][v] = pv;
    for (const auto &e: G[v]) {
      if (e.to != pv) {
        depth[e.to] = depth[v]+1;
        dfs(e.to, v);
        dp[0][e.to] = e.cost;
      }
    }
  }

public:
  LCA(const int n, const int _root) : is_build(false), size(n), log_size(0), root(_root), depth(size, 0), G(n) {
    for (int v = size; v > 0; v /= 2) ++log_size;
  }
  void add(int a, int b, T c) {
    G[a].push_back({b, c});
    G[b].push_back({a, c});
  }
  void build() {
    is_build = true;
    parent.assign(log_size, vector<int>(size, -1));
    dp.assign(log_size, vector<T>(size, Monoid::id()));
    dfs(root, -1);
    for (int k = 0; k < log_size - 1; ++k) for (int v = 0; v < size; ++v) {
      if (parent[k][v] < 0) {
        parent[k+1][v] = -1;
        dp[k+1][v] = dp[k][v];
      }
      else {
        parent[k+1][v] = parent[k][parent[k][v]];
        dp[k+1][v] = Monoid::op(dp[k][v], dp[k][parent[k][v]]);
      }
    }
  }
  pair<int, T> lca(int u, int v) {
    if (!is_build) build();
    if (depth[u] > depth[v]) std::swap(u, v);
    T res = Monoid::id();
    for (int k = 0; k < log_size; ++k) {
      if (((depth[v] - depth[u]) >> k) & 1) {
        res = Monoid::op(res, dp[k][v]);
        v = parent[k][v];
      }
    }
    if (u == v) return {u, res};
    for (int k = log_size - 1; ~k; --k) {
      if (parent[k][u] != parent[k][v]) {
        res = Monoid::op(res, dp[k][u]);
        res = Monoid::op(res, dp[k][v]);
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    //~ assert(parent[0][u] == parent[0][v]);
    res = Monoid::op(res, dp[0][u]);
    res = Monoid::op(res, dp[0][v]);
    return {parent[0][u], res};
  }
};
struct Min {
  using type = ll;
  static type id() { return linf; }
  static type op(const type &l, const type &r) { return min(l, r); }
};
struct Max {
  using type = ll;
  static type id() { return -linf; }
  static type op(const type &l, const type &r) { return max(l, r); }
};
struct Sum {
  using type = ll;
  static type id() { return 0; }
  static type op(const type &l, const type &r) { return l + r; }
};

/*************************************/
// raw
const int N = 2e5 + 42, LN = 18;
vector<int> g[N];
int ent[N];
int ext[N];
int dep[N];
int par[LN][N];

int lca(int u, int v) {
  if (ent[u] > ent[v]) swap(u, v);
  if (ent[u] < ent[v] && ext[v] < ext[u]) return u;
  for (int i = LN - 1; ~i; --i) {
    if (ent[par[i][u]] < ent[v] && ext[v] < ext[par[i][u]]) continue;
    u = par[i][u];
  }
  return par[0][u];
}
void dfs(int u, int p = 0) {
  static int tick = 0;
  par[0][u] = p;
  for (int i = 1; i < LN; ++i)
    par[i][u] = par[i - 1][par[i - 1][u]];
  ent[u] = tick++;
  for (int v : g[u]) if (v != p) {
    dep[v] = 1 + dep[u];
    dfs(v, u);
  }
  ext[u] = tick++;
}

void read(int n) {
  //~ for (int i = 0; i < n; ++i) g[i].clear();
for (int i = 0; i < n - 1; ++i) {
  int u, v; cin >> u >> v;
  --u, --v;
  g[u].push_back(v);
  g[v].push_back(u);
}
} 
