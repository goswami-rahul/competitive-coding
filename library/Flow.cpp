namespace Flow {
  typedef int flow_t;
  typedef vector<vector<int>> graph_t;
  const int MAXN = 128;
  const flow_t INF = 2e9;
  static flow_t residual[MAXN][MAXN];
  static int parent[MAXN];
  static flow_t _flow[MAXN];
  int source, sink;
  
  flow_t find_flow(const graph_t &g) {
    memset(parent, -1, sizeof parent);
    parent[source] = -2;
    _flow[source] = INF;
    vector<int> que; int qf = 0;
    que.push_back(source);
    while (qf < (int) que.size()) {
      int u = que[qf++];
      for (const int &v: g[u]) if (parent[v] == -1 && residual[u][v] > 0) {
        parent[v] = u;
        _flow[v] = min(residual[u][v], _flow[u]);
        if (v == sink) return _flow[sink];
        que.push_back(v);
      }
    }
    return 0;
  }
  
  flow_t max_flow(const graph_t &g, int from, int to) {
    source = from, sink = to;
    flow_t flow = 0, cur_flow;
    while ((cur_flow = find_flow(g)) > 0) {
      flow += cur_flow;
      for (int v = sink; v != source; v = parent[v]) {
        int u = parent[v];
        residual[u][v] -= cur_flow;
        residual[v][u] += cur_flow;
      }
    }
    return flow;
  }
  void reset_residual() {
    memset(residual, 0, sizeof residual);
  }
}
