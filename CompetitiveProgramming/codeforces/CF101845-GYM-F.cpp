/**
 * Construct a flow network with edges from source to each team with capacity 1,
 * and from each career to sink with capacity k.
 * Connect edges from the teams to the careers which they can be assigned
 * with capacity 1
 * The maximum flow from the source to the sink is the answer.
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
int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<vector<int>> g(n + 26 + 2);
  Flow::reset_residual();
  for (int i = 0; i < n; ++i) {
    vector<int> cnt(26);
    for (int j = 0; j < 3; ++j) {
      string s; cin >> s;
      for (char c: s) ++cnt[c - 'A'];
    }
    int mx = *max_element(ALL(cnt));
    for (int j = 0; j < 26; ++j) if (cnt[j] == mx) {
      g[i].push_back(n + j);
      g[n + j].push_back(i);
      Flow::residual[i][n + j] = 1;
    }
  }
  int k; cin >> k;
  int s = n + 26, t = s + 1;
  for (int i = 0; i < n; ++i) {
    g[s].push_back(i);
    g[i].push_back(s);
    Flow::residual[s][i] = 1;
  }
  for (int i = n; i < n + 26; ++i) {
    g[t].push_back(i);
    g[i].push_back(t);
    Flow::residual[i][t] = k;
  }
  cout << Flow::max_flow(g, s, t) << '\n';
  
  return 0;
}
