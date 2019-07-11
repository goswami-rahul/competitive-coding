/**
 * For the maximum number of cars on all paths simultaneously,
 * we can find the max flow of the graph from A to B.
 * And to find the path with maximum flow, we can binary search for the
 * threshold of capacities above which which all roads are allowed, and 
 * a path from A to B exists.
 * For fast maximum flow, we can Dinic's algorithm, which runs in 0.03s
 * for this problem.
 * We can also use Dinic's algorithm with scaling, for better complexity,
 * which runs in 0.00s, fastest submission on that problem.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef unsigned long long i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string>) {}
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2> buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (const auto e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
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

using namespace Dinic;
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int tt; cin >> tt;
  while (tt--) {
    int tno, n, m, a, b;
    cin >> tno >> n >> m >> a >> b;
    vector<vector<pair<int,int>>> g(n);
    Dinic::reset(n);
    int max_w = 0;
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      uax(max_w, w);
      g[u].emplace_back(v, w);
      Dinic::set_edge(u, v, w);
    }
    int mf = Dinic::max_flow(a, b);
    int lo = 1, hi = max_w;
    while (lo < hi) {
      int md = (lo + hi + 1) >> 1;
      vector<bool> vis(n, false);
      vector<int> nodes = {a};
      vis[a] = true;
      while (!nodes.empty()) {
        int u = nodes.back();
        if (u == b) break;
        nodes.pop_back();
        for (const auto &e: g[u]) if (!vis[e.first] && e.second >= md) {
          vis[e.first] = true;
          nodes.push_back(e.first);
        }
      }
      if (vis[b]) lo = md;
      else hi = md - 1; 
    }
    
    double ans = (double) mf / lo;
    cout.precision(3);
    cout << fixed << tno << " " << ans << '\n';
  }
  
  return 0;
}
