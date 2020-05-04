// with rollback
struct info {
  int u, szu, v, szv;
};
info op[N];
struct UF {
  vector<int> par, sizes;
  int ptr;
  UF(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    sizes.assign(n, 1);
    ptr = 0;
  }
  int find(int u) {
    return (u == par[u] ? u : find(par[u]));
  }
  bool join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (sizes[u] < sizes[v]) swap(u, v);
    op[ptr++] = {u, sizes[u], v, sizes[v]};
    par[v] = u;
    sizes[u] += sizes[v];
    return true;
  }
  void roll() {
    info &x = op[--ptr];
    par[x.u] = x.u;
    sizes[x.u] = x.szu;
    par[x.v] = x.v;
    sizes[x.v] = x.szv;
  }
  int size(int u) {
    return sizes[find(u)];
  }
};

// with compression
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
