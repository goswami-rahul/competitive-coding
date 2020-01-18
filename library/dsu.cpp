struct UF {
  vector<int> par, sizes;
  int cnt;
  UF(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    sizes.assign(n, 1);
    cnt = n;
  }
  int find(int u) {
    return (u == par[u] ? u : par[u] = find(par[u]));
  }
  bool join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (rand() % 2) swap(u, v);
    par[v] = u;
    sizes[u] += sizes[v];
    cnt--;
    return true;
  }
  int size(int u) {
    return sizes[find(u)];
  }
  int is_leader(int u) {
    return u == find(u);
  }
};
