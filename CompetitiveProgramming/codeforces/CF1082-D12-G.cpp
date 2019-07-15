/**
 * The problem seems to variation of a well-known problem "Projects and Instruments".
 * We construct a network flow graph
 * Represent the edges and vertices of the original graph as nodes in
 * the flow network.
 * Connect the source to the nodes representing edges with their weights,
 * and the nodes representing vertices to the sink with their weights.
 * Also connect each edge node with 2 vertex nodes to which it belongs
 * with capacity infinity.
 * Now, consider a min cut of this network.
 * If an edge on the right side (connected to sink) belongs to the cut,
 * we use that vertex in our subgraph.
 * Also, if an edge of the left side (connected to source) belongs to the cut,
 * we discard this edge from our subgraph, since we didn't take its vertices.
 * 
 * The min cut cost equals vertices taken + edges discarded.
 * Thus, the answer is total edge weights - min cut cost.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef long long i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
string to_string(char c) { return "'" + string(1, c) + "'";}
string to_string(string s) { return '"' + s + '"';}
string to_string(const char* s) { return to_string((string) s);}
template<typename A> string to_string(A);
template<typename A, typename B> string to_string(pair<A, B> p){
  return "(" + to_string(p.first) + ": " + to_string(p.second) + ")";}
template<typename A> string to_string(A v) {bool f = false; string r = "{"; 
  for (auto x: v) {if (f) r += ", "; r += to_string(x); f = true;} return r += "}";}
template<typename A> string to_string(vector<vector<A>> v) {string r; 
  for (auto x: v) r += "\n" + to_string(x); return r;}
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
namespace Dinic {
  
typedef i64 flow_t;
const int MAXN = 2e3 + 5;
const int MAXE = 8e3 + 5;
const flow_t INF = 2e18;
const flow_t EPS = 1;

flow_t LIM = EPS;

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
// scale = max capacity edge if scaling else default
flow_t max_flow(int s, int t, int scale = EPS) {
  source = s, sink = t;
  flow_t flow = 0, pushed;
  for (LIM = scale; LIM >= EPS; LIM >>= 1) {
    while (bfs()) {
      fill(ptr, ptr + N, 0);
      while ((pushed = dfs(source, INF)) >= EPS) 
        flow += pushed;
    }
  }
  return flow;
}
inline void reset(int n = MAXN) {
  N = n; E = 0;
  for (int i = 0; i < N; ++i) adj[i].clear();
}
inline void set_edge(int u, int v, flow_t cap = 1) /*directed edge*/ {
  adj[u].push_back(E);
  edges[E++] = {u, v, cap, 0};
  adj[v].push_back(E);
  edges[E++] = {v, u, 0, 0};
}

} // namespace Dinic

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, m;
  cin >> n >> m;
  int s = n + m, t = 1 + s;
  int max_w = 0;
  for (int i = 0; i < n; ++i) {
    int w; cin >> w;
    uax(max_w, w);
    Dinic::set_edge(i, t, w);
  }
  i64 e_weights = 0LL;
  for (int i = 0; i < m; ++i) {
    int u, v, w; cin >> u >> v >> w;
    uax(max_w, w);
    e_weights += w;
    --u; --v;
    Dinic::set_edge(s, i + n, w);
    Dinic::set_edge(i + n, u, Dinic::INF);
    Dinic::set_edge(i + n, v, Dinic::INF);
  }
  cout << e_weights - Dinic::max_flow(s, t) << '\n';
  
  return 0;
}
