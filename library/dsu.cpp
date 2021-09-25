// with rollback
struct info {
  int u, szu, v, szv;
};
info op[N];
struct UnionFind {
  vector<int> par, sz;
  int ptr;
  UnionFind(int n): par(n), sz(n, 1), ptr(0) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int u) {
    return (u == par[u] ? u : find(par[u]));
  }
  bool join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    op[ptr++] = {u, sz[u], v, sz[v]};
    par[v] = u;
    sz[u] += sz[v];
    return true;
  }
  void roll() {
    info &x = op[--ptr];
    par[x.u] = x.u;
    sz[x.u] = x.szu;
    par[x.v] = x.v;
    sz[x.v] = x.szv;
  }
  int size(int u) {
    return sz[find(u)];
  }
};

// with compression
struct UnionFind {
  vector<int> par, sz;
  UnionFind(int n): par(n), sz(n, 1) {
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
};
