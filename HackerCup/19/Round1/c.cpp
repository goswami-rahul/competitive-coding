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
namespace Flow {
  typedef int flow_t;
  const int MAXN = 64;
  const flow_t INF = 2e9;
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
      for (const int &v: g[u]) if (parent[v] == -1 && residual[u][v] > 0) {
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
    while ((cur_flow = find_flow()) > 0) {
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
struct item {
  int x, y1, y2;
  bool operator < (const item &rhs) const {
    return x < rhs.x;
  }
};
ostream& operator << (ostream &os, item a) {
  return os << "(" << a.x << ", " << a.y1 << ", " << a.y2 << ")";
}
void Run() {
  int n, h;
  cin >> n >> h;
  vector<item> ladders(n);
  for (auto &a: ladders) 
    cin >> a.x >> a.y1 >> a.y2;
  sort(ALL(ladders));
  Flow::reset();
  for (int i = 1; i < h - 1; ++i) {
    vector<int> a;
    for (int j = 0; j < n; ++j) {
      if (ladders[j].y1 <= i && i < ladders[j].y2) {
        a.push_back(j);
      }
    }
    for (int j = 0; j < SZ(a); ++j) {
      if (j > 0) Flow::add_edge(a[j], a[j - 1], 1);
      if (j + 1 < SZ(a)) Flow::add_edge(a[j], a[j + 1], 1);
    }
  }
  int s = 50, t = 51;
  for (int i = 0; i < n; ++i) {
    if (ladders[i].y1 == 0) Flow::set_edge(s, i, Flow::INF);
    if (ladders[i].y2 == h) Flow::set_edge(i, t, Flow::INF);
  }
  int flow = Flow::max_flow(s, t);
  cout << (flow == Flow::INF ? -1 : flow) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int tt;
  cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    cout << "Case #" << i << ": ";
    Run();
  }

  return 0;
} 
