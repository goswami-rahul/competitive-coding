struct Dsu {
  vector<int> par, sz;
  Dsu(int n): par(n), sz(n, 1) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int u) {
    return (u == par[u] ? u : par[u] = find(par[u]));
  }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    par[v] = u;
    sz[u] += sz[v];
    return true;
  }
  int size(int u) {
    return sz[find(u)];
  }
  bool same(int u, int v) {
    return find(u) == find(v);
  }
};
