/*
First, find all the bridges of the graph and remove those bridges.
then for each connected component, count the number of choosing 2 nodes
such that both belong to a same connected component. Let it be val.
Then the required probability is [1 - ans / total]
total = n * (n - 1) / 2
*/
#include<bits/stdc++.h>
using namespace std;
using i64 = long long int;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> tin(n, -1), fup(n, -1), sz(n, -1);
    vector<bool> vis(n, false);
    int timer = 0;
    function<void(int,int)> dfs = [&] (int u, int pa) {
        tin[u] = timer++;
        sz[u] = 1;
        fup[u] = tin[u];
        vis[u] = true;
        vector<int> temp;
        for (int v: g[u]) {
            if (v == pa) continue;
            if (vis[v]) {
                fup[u] = min(fup[u], tin[v]);
            } else {
                dfs(v, u);
                sz[u] += sz[v];
                fup[u] = min(fup[u], fup[v]);
                if (fup[v] > tin[u]) {
                    // bridge
                } else {
                    temp.push_back(v);
                }
            }
        }
        g[u] = temp;
    };
    dfs(0, -1);
    vis.assign(n, false);
    i64 cnt;
    function<void(int)> calc = [&] (int u) {
        cnt++;
        vis[u] = true;
        for (int v: g[u]) calc(v);
    };
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            cnt = 0;
            calc(i);
            ans += cnt * (cnt - 1) / 2;
        }
    }
    cout << fixed << setprecision(5) << 1 - (long double) ans * 2 / n / (n - 1) << '\n';

    return 0;
}
