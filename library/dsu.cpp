struct DSU {
    vector<int> par;
    DSU(int n) {
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
    }
    inline int find(int u) {
        return (u == par[u] ? u : par[u] = find(par[u]));
    }
    inline bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (rand() % 2) swap(u, v);
        par[v] = u;
        return true;
    }
};
