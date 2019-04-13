template<class Monoid>
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
    each(e, G[v]) {
      if (e.to != pv) {
        depth[e.to] = depth[v]+1;
        dfs(e.to, v);
        dp[0][e.to] = e.cost;
      }
    }
  }

public:
  LCA(const int n, const int root) : is_build(false), size(n), log_size(0), root(root), depth(size, 0), G(n) {
    for (int v = size; v > 0; v /= 2) ++log_size;
  }
  void add(int a, int b, T c) {
    G[a].pb({b, c});
    G[b].pb({a, c});
  }
  void build() {
    is_build = true;
    parent.assign(log_size, vector<int>(size, -1));
    dp.assign(log_size, vector<T>(size, Monoid::id()));
    dfs(root, -1);
    rep(k, log_size-1) rep(v, size) {
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
    rep(k, log_size) {
      if (((depth[v] - depth[u]) >> k) & 1) {
        res = Monoid::op(res, dp[k][v]);
        v = parent[k][v];
      }
    }
    if (u == v) return {u, res};
    rrep(k, log_size) {
      if (parent[k][u] != parent[k][v]) {
        res = Monoid::op(res, dp[k][u]);
        res = Monoid::op(res, dp[k][v]);
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    // assert(parent[0][u] == parent[0][v]);
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
