#include<bits/stdc++.h>
using namespace std;
using i64 = long long int;
#define all(vec) (vec).begin(),(vec).end()
const int MOD = 1e9 + 7;
const long long INF = 1e18;
/***********************************************************************/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<int> roots;
    map<string,int> mpp;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        mpp[s[i]];
        int u;
        cin >> u; --u;
        if (u != -1)
            tree[u].push_back(i);
        else
            roots.push_back(i);
    }
    int id = 0;
    for (auto& [ignore, val]: mpp) val = id++;
    vector<int> M(n);
    for (int i = 0; i < n; ++i) {
        M[i] = mpp[s[i]];
    }
    vector<int> sz(n), big(n, -1), h(n);
    function<void(int)> pre = [&] (int u) {
        sz[u] = 1;
        int mx = -1;
        for (int &v: tree[u]) {
            h[v] = 1 + h[u];
            pre(v);
            sz[u] += sz[v];
            if (sz[v] > mx) {
                mx = sz[v];
                big[u] = v;
            }
        }
    };
    for (int r: roots) {
        h[r] = 0;
        pre(r);
    }
    vector<vector<pair<int,int>>> Q(n);
    cin >> m;
    vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
        int v, k;
        cin >> v >> k;
        --v;
        Q[v].emplace_back(i, k + h[v]);
    }
    using H = unordered_map<int, set<int>>;
    function<void(int, H&)> dfs = [&] (int u, H &my) {
        if (!tree[u].empty()) {
            dfs(big[u], my);
            for (int &v: tree[u]) {
                if (v == big[u]) continue;
                H his;
                dfs(v, his);
                for (auto& [hh, x]: his)
                    my[hh].insert(all(x));
            }
        }
        my[h[u]].insert(M[u]);
        for (auto& [id, hh]: Q[u]) {
            if (my.count(hh)) ans[id] = (int) my[hh].size();
            else ans[id] = 0;
        }
    };
    for (int r: roots) {
        H a;
        dfs(r, a);
    }
    for (auto x: ans) cout << x << '\n';

    return 0;
}
