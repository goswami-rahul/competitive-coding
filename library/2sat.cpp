struct Sat {
  vector<vector<int>> g;
  vector<vector<int>> r;
  int n;
  vector<int> order, which, answer;
  Sat(int variables) : n(variables << 1) {
    g.resize(n);
    r.resize(n);
  }
  // add u << 1 for u, u << 1 | 1 for ~u
  void implies(int u, int v) {
    // u => v
    g[u].push_back(v);
    r[v].push_back(u);
    // ~v => ~u
    g[v ^ 1].push_back(u ^ 1);
    r[u ^ 1].push_back(v ^ 1);
  }
  bool solve() {
    order = {};
    which.assign(n, 0);
    for (int u = 0; u < n; ++u) {
      if (!which[u]) dfs1(u);
    }
    which.assign(n, -1);
    int ccnt = 0;
    for (int i = n - 1; i >= 0; --i) {
      int u = order[i];
      if (which[u] == -1) dfs2(u, ccnt++);
    }
    answer.assign(n >> 1, 0);
    for (int u = 0; u < n; u += 2) {
      if (which[u] == which[u ^ 1]) return false;
      answer[u >> 1] = which[u] > which[u ^ 1];
    }
    return true;
  }
  void dfs1(int u) {
    which[u] = 1;
    for (int v : g[u]) if (!which[v]) dfs1(v);
    order.push_back(u);
  }
  void dfs2(int u, int cc) {
    which[u] = cc;
    for (int v : r[u]) if (which[v] == -1)
      dfs2(v, cc);
  }
};
