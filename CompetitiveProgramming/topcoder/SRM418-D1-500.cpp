/**
 * First, we can observe that such stamps which are demanded by only
 * 1 buyer, can be directly sold that buyer.
 * Now, consider such stamps which are demanded by 2 buyers. We can 
 * only sell it to only one of them, so lets create graph,
 * with vertices as buyers, and edges if they both demand a same stamp.
 * We obtain a graph with vertices with degrees at most 2.
 * Every connected component in this graph will be either a chain,
 * or a cycle.
 * If we keep the prices at each vertex, the problem becomes to find the
 * maximum weight independent set.
 * But since, the graph has only chains and cycles, we can linearize the
 * components and find the optimal prixes with dp.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()

class StampsCollection {
public:
  vector<vector<int>> adj;
  vector<int> price;
  vector<bool> vis;
  int m;
  int go(int u) {
    for (int v = 0; v < m; ++v) 
      if (adj[u][v] && !vis[v]) return v;
    return -1;
  }
  using It = vector<int>::iterator;
  int solve(It it, It ti) {
    int max1 = 0, max2 = 0;
    for (; it != ti; ++it) {
      int cur = *it + max2;
      max2 = max(max1, max2), max1 = max(max1, cur);
    }
    return max(max1, max2);
  }
  int sell(int n, vector<string> demand, vector<int> _price) {
    price = _price;
    m = (int) demand.size();
    vector<vector<int>> need(n);
    for (int i = 0; i < m; ++i) {
      istringstream str(demand[i]);
      for (int u; str >> u; ) {
        need[u].push_back(i);
      }
    }
    adj.assign(m, vector<int>(m));
    for (auto &vs: need) {
      for (int i = 0; i < SZ(vs); ++i) for (int j = i + 1; j < SZ(vs); ++j) {
        adj[vs[i]][vs[j]] = adj[vs[j]][vs[i]] = 1;
      }
    }
    int ans = 0;
    vis.assign(m, false);
    for (int u = 0; u < m; ++u) {
      int deg = accumulate(ALL(adj[u]), 0);
      if (vis[u]) continue;
      if (deg == 0) {
        vis[u] = true;
        ans += price[u];
      }
      if (deg == 1) {
        // chain
        vector<int> a;
        vector<int> chain;
        for (int v = u; v != -1; v = go(v)) {
          assert (!vis[v]);
          vis[v] = true;
          a.push_back(price[v]);
          chain.push_back(v);
        }
        int cur = solve(a.begin(), a.end());
        ans += cur;
      }
    }
    // cycles
    for (int u = 0; u < m; ++u) {
      if (vis[u]) continue;
      vector<int> a, b;
      vector<int> cycle;
      for (int v = u; v != -1; v = go(v)) {
        vis[v] = true;
        a.push_back(price[v]);
        cycle.push_back(v);
      }
      b = a;
      a.insert(a.end(), b.begin(), b.end());
      assert(SZ(a) > 2);
      int cur = 0;
      for (int i = 0; i < SZ(b); ++i) {
        cur = max(cur, a[i + 1] + solve(a.begin() + i + 3, a.begin() + i + SZ(b)));
      }
      ans += cur;
    }
    return ans;
  }
};
