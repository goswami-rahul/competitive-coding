/**
 * First take logarithms of the cost to translate the multiplication to addition.
 * Consruct flow network with vertices being rows and columns, and edges
 * between them with infinite capacities for each paratroopers row to column;
 * Problem is to find the minimum weight vertex cover of this graph.
 * This is equivalent to finding min cut of the Flow network, with source
 * connected to rows with edges capacities equal to their cost, similarly
 * columns to sink.
 * Finally print exponential of the min cut as the answer.
**/
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

namespace Flow {
  typedef double flow_t;
  const int MAXN = 128;
  const flow_t INF = 1.0 / 0.0;
  const flow_t EPS = 1e-9;
  static vector<int> g[MAXN];
  static flow_t residual[MAXN][MAXN];
  static int parent[MAXN];
  static flow_t _flow[MAXN];
  int source, sink;
  
  flow_t find_flow() {
    memset(parent, -1, sizeof parent);
    parent[source] = -2;
    _flow[source] = Flow::INF;
    vector<int> que; int qf = 0;
    que.push_back(source);
    while (qf < (int) que.size()) {
      int u = que[qf++];
      for (int i = 0; i < (int) g[u].size(); ++i) {
        int v = g[u][i];
        if (parent[v] == -1 && residual[u][v] > EPS) {
          parent[v] = u;
          _flow[v] = min(residual[u][v], _flow[u]);
          if (v == sink) return _flow[sink];
          que.push_back(v);
        }
      }
    }
    return 0;
  }
  flow_t max_flow(int from, int to) {
    source = from, sink = to;
    flow_t flow = 0, cur_flow;
    while ((cur_flow = find_flow()) > EPS) {
      if (cur_flow == Flow::INF) return Flow::INF;
      flow += cur_flow;
      for (int v = sink; v != source; v = parent[v]) {
        int u = parent[v];
        residual[u][v] -= cur_flow;
        residual[v][u] += cur_flow;
      }
    }
    return flow;
  }
  inline void reset() {
    memset(residual, 0, sizeof residual);
    for (int i = 0; i < MAXN; ++i) g[i].clear();
  }
  inline void set_edge(int u, int v, flow_t cap) /*directed edge*/ {
    g[u].push_back(v);
    g[v].push_back(u);
    residual[u][v] = cap;
  }
  inline bool is_edge(int u, int v) {
    return residual[u][v] > 0 || residual[v][u] > 0;
  }
  inline void add_edge(int u, int v, flow_t cap) /*directed edge*/ {
    if (!is_edge(u, v)) return set_edge(u, v, cap);
    residual[u][v] += cap;
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m, p;
    cin >> n >> m >> p;
    Flow::reset();
    int s = n + m, t = s + 1;
    for (int i = 0; i < n; ++i) {
      double w; cin >> w;
      Flow::set_edge(s, i, log(w));
    }
    for (int i = n; i < n + m; ++i) {
      double w; cin >> w;
      Flow::set_edge(i, t, log(w));
    }
    while (p--) {
      int r, c;
      cin >> r >> c;
      --r;
      --c;
      c += n;
      Flow::set_edge(r, c, Flow::INF);
    }
    cout.precision(4);
    cout << fixed << exp(Flow::max_flow(s, t)) << '\n';
  }
 
  return 0;
} 
