namespace Dinic {
  
typedef int flow_t;
const int MAXN = 1000;
const int MAXE = MAXN * MAXN;
const flow_t INF = 2e9;
const flow_t EPS = 1;

const bool SCALING = true;
flow_t MAXCAP = 1000;
flow_t LIM = SCALING ? MAXCAP : EPS;

struct Edge {
  int u, v;
  flow_t cap, flow;
};
Edge edges[MAXE];
vector<int> adj[MAXN];
int lev[MAXN];
int ptr[MAXN];
int que[MAXN];
int N = MAXN, E = 0;
int source, sink;

bool bfs() {
  int fp = 0, bp = 0;
  fill(lev, lev + N, -1);
  lev[source] = 0; que[bp++] = source;
  while (fp < bp) {
    int u = que[fp++];
    for (const int id : adj[u]) {
      if (edges[id].cap - edges[id].flow < LIM) continue;
      if (lev[edges[id].v] != -1) continue;
      lev[edges[id].v] = lev[u] + 1;
      que[bp++] = edges[id].v;
    }
  }
  return lev[sink] != -1;
}
flow_t dfs(int u, flow_t pushed) {
  if (pushed == 0) return 0;
  if (u == sink) return pushed;
  for (int& cid = ptr[u]; cid < (int) adj[u].size(); cid++) {
    int id = adj[u][cid];
    int v = edges[id].v;
    if (lev[u] + 1 != lev[v]) continue;
    if (edges[id].cap - edges[id].flow < LIM) continue;
    flow_t flow = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
    if (flow == 0) continue;
    edges[id].flow += flow;
    edges[id ^ 1].flow -= flow;
    return flow;
  }
  return 0;
}
flow_t max_flow(int s, int t) {
  source = s, sink = t;
  flow_t flow = 0, pushed;
  for (; LIM >= EPS; LIM >>= 1) {
    while (bfs()) {
      fill(ptr, ptr + N, 0);
      while ((pushed = dfs(source, INF)) >= EPS) 
        flow += pushed;
    }
  }
  return flow;
}
inline void reset(int n = MAXN, int maxcap = MAXCAP) {
  N = n; E = 0; LIM = SCALING ? maxcap : EPS;
  for (int i = 0; i < N; ++i) adj[i].clear();
}
inline void set_edge(int u, int v, flow_t cap = 1) /*directed edge*/ {
  adj[u].push_back(E);
  edges[E++] = {u, v, cap, 0};
  adj[v].push_back(E);
  edges[E++] = {v, u, 0, 0};
}

} // namespace Dinic

/*****************************************************/

namespace Flow {

typedef int flow_t;
const int MAXN = 128;
const flow_t INF = 2e9;
const flow_t EPS = 1;
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
    for (const int &v: g[u]) if (parent[v] == -1 && residual[u][v] >= EPS) {
      parent[v] = u;
      _flow[v] = min(residual[u][v], _flow[u]);
      if (v == sink) return _flow[sink];
      que.push_back(v);
    }
  }
  return 0;
}
flow_t max_flow(int from, int to) {
  source = from, sink = to;
  flow_t flow = 0, cur_flow;
  while ((cur_flow = find_flow()) >= EPS) {
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
  return residual[u][v] >= EPS || residual[v][u] >= EPS;
}
inline void add_edge(int u, int v, flow_t cap) /*directed edge*/ {
  if (!is_edge(u, v)) return set_edge(u, v, cap);
  residual[u][v] += cap;
}
} // namespace Flow
