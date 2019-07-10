/**
 * The square is valid if and only if for each digit 0 < d < 9,
 * We can match all of the (d + 1)s to one d each.
 * Since we can find the maximum matching for d and (d + 1)s positions,
 * and check if it is equal to frequency of d + 1.
 * To calculate maximum matching efficiently, we can use Dinic's max flow 
 * algorithm, which can calculate maxflow for Unit networks in (E sqrt(V)).
 * To create the network, all the edges between two nodes if (d + 1) is
 * adjacent to any d, with capacity 1.
 * Connnect source node to (d)s with capacity infinity
 * Connnect all (d + 1)s to sink node with capacity infinity
 * The max flow from source to sink is the maximum matching.
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
const int MAXN = 10010;
const int MAXE = MAXN << 3;
const flow_t INF = 2e9;
const flow_t EPS = 1;

struct Edge {
  int u, v;
  flow_t cap, flow;
};
static Edge edges[MAXE];
static vector<int> adj[MAXN];
static int lev[MAXN];
static int ptr[MAXN];
static int que[MAXN];
int N = MAXN, E = 0;
int source, sink;

bool bfs() {
  int fp = 0, bp = 0;
  fill(lev, lev + N, -1);
  lev[source] = 0; que[bp++] = source;
  while (fp < bp) {
    int u = que[fp++];
    for (const int id : adj[u]) {
      if (edges[id].cap - edges[id].flow < EPS) continue;
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
    if (edges[id].cap - edges[id].flow < EPS) continue;
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
  while (bfs()) {
    fill(ptr, ptr + N, 0);
    while ((pushed = dfs(source, INF)) >= EPS) 
      flow += pushed;
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

const int nax = 101;
int a[nax][nax], m[nax][nax];
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> cnt(10, 0);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) { 
      cin >> a[i][j];
      m[i][j] = cnt[a[i][j]]++;
    }
    bool ok = true;
    for (int k = 1; k < 9 && ok; ++k) {
      if (cnt[k + 1] == 0) {
        for (int i = k + 1; i < 10; ++i) ok &= cnt[i] == 0;
        break;
      }
      Dinic::reset(cnt[k] + cnt[k + 1] + 2);
      int s = cnt[k] + cnt[k + 1], t = s + 1;
      for (int i = 0; i < cnt[k]; ++i) 
        Dinic::set_edge(s, i);
      for (int i = 0; i < cnt[k + 1]; ++i) 
        Dinic::set_edge(cnt[k] + i, t);
      for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (a[i][j] == k) {
        if (i + 1 < n && a[i + 1][j] == k + 1)
          Dinic::set_edge(m[i][j], cnt[k] + m[i + 1][j]);
        if (i > 0 && a[i - 1][j] == k + 1)
          Dinic::set_edge(m[i][j], cnt[k] + m[i - 1][j]);
        if (j + 1 < n && a[i][j + 1] == k + 1)
          Dinic::set_edge(m[i][j], cnt[k] + m[i][j + 1]);
        if (j > 0 && a[i][j - 1] == k + 1)
          Dinic::set_edge(m[i][j], cnt[k] + m[i][j - 1]);
      }
      ok &= Dinic::max_flow(s, t) == cnt[k + 1];
    }
    cout << (ok ? "YES\n" : "NO\n");
  }
  
  return 0;
}
