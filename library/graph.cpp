function<void(int, int, ll, int)> dfs = [&] (int s, int pa = -1, int dep = 0) {
    depth[s] = dep;
    par[s][0] = pa;
    for (int i = 1; i < LOGN; ++i)
        if (par[s][i - 1] != -1)
            par[s][i] = par[par[s][i - 1]][i - 1];
    for (auto d: g[s]) {
        if (d == pa)
            continue;
        make_tree(d, s, dep + 1);
    }
};
function<int(int, int)> lca = [&] (int a, int b) {
    if (depth[b] < depth[a])
        swap(a, b);
    for (int i = LOGN - 1; i >= 0; --i)
        if (par[b][i] != -1 && depth[par[b][i]] >= depth[a])
            b = par[b][i];
    assert(depth[a] == depth[b]);
    if (a == b)
        return a;
    for (int i = LOGN - 1; i >= 0; --i)
        if (par[a][i] != par[b][i])
            a = par[a][i], b = par[b][i];
    assert(par[a][0] == par[b][0]);
    return par[a][0];
};
