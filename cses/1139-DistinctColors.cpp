#include <bits/stdc++.h>
using namespace std;
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  vector<int> a(n), b;
  for (int &z: a) cin >> z;
  b = a; sort(ALL(b));
  b.erase(unique(ALL(b)), b.end());
  for (int &z: a) {
    z = (int) (lower_bound(ALL(b), z) - b.begin());
  }
  for (int i = 0; i < n - 1; ++i) {
    int u, v; cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> ans(n), size(n);
  function<void(int,int)>
  get_size = [&] (int u, int p) {
    int big_size = -1;
    for (const int &v: g[u]) if (v != p) {
      get_size(v, u);
      size[u] += size[v];
      uax(big_size, size[v]);
    }
    for (int &v: g[u]) if (v != p) {
      if (size[v] == big_size) {
        swap(v, g[u].back());
        break;
      }
    }
    size[u]++;
  };
  function<void(int,int,set<int>&)>
  dfs = [&] (int u, int p, set<int>& s) {
    if (size[u] > 1) {
      dfs(g[u].back(), u, s);
      g[u].pop_back();
      for (const int &v: g[u]) if (v != p) {
        set<int> ns;
        dfs(v, u, ns);
        for (const int &z: ns) s.insert(z);
      }
    }
    s.insert(a[u]);
    ans[u] = (int) s.size();
  };
  get_size(0, -1);
  set<int> s;
  dfs(0, -1, s);
  for (const auto &z: ans) cout << z << ' ';
  
  return 0;
}
