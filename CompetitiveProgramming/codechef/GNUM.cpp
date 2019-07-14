/**
 * The problem is equivalent to bipartite maximum matching and can be solved by
 * Max flow min cut.
 * let X be all g such that (ai < bi and (g = gcd(ai, bi)) > 1)
 * let Y be all g such that (ai > bi and (g = gcd(ai, bi)) > 1)
 * make edges with infinite capacities from each node gx, in X,
 * to each node gy in Y, where gcd(gx, gy) > 1.
 * To reduce the number of nodes and edges, compress the graph, by
 * removing duplicate nodes, and edges from source to nodes in X with equal to 
 * their counts. Similarly, add edges from Y to sink.
 * Run the max flow algorithm on this graph
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
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
namespace Dinic {
  
typedef int flow_t;
const int MAXN = 400 * 400;
const int MAXE = 5e7;
const flow_t INF = 2e9;
const flow_t EPS = 1;

const bool SCALING = false;
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

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int &z: a) cin >> z;
    for (int &z: b) cin >> z;
    map<int,int> x, y;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) if (a[i] != b[j]) {
        if (a[i] < b[j] && __gcd(a[i], b[j]) > 1)
          x[__gcd(a[i], b[j])]++;
        if (a[i] > b[j] && __gcd(a[i], b[j]) > 1)
          y[__gcd(a[i], b[j])]++;
      }
    }
    Dinic::reset(SZ(x) + SZ(y) + 2);
    int s = SZ(x) + SZ(y), t = s + 1;
    auto it = x.begin();
    for (int i = 0; i < SZ(x); ++i, ++it) {
      Dinic::set_edge(s, i, it->second);
    }
    it = y.begin();
    for (int i = 0; i < SZ(y); ++i, ++it) {
      Dinic::set_edge(i + SZ(x), t, it->second);
    }
    it = x.begin();
    for (int i = 0; i < SZ(x); ++i, ++it) {
      auto it2 = y.begin();
      for (int j = 0; j < SZ(y); ++j, ++it2) {
        if (__gcd(it->first, it2->first) > 1) {
          Dinic::set_edge(i, j + SZ(x), Dinic::INF);
        }
      }
    }
    cout << Dinic::max_flow(s, t) << '\n';
  }
  
  return 0;
}
