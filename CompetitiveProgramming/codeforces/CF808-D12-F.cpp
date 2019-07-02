/**
 * This solution is same as given in the editorial https://codeforces.com/blog/entry/52010
 * We construct the graph with vertices as cards, and edges if sum of cards 
 * is a prime number.
 * The problem reduces to finding the maximum weighted independent set.
 * This problem if NP hard in general, but solvable in bipartite graphs using min cut
 * Our graph is a bipartite graph with odd one side and even on another.
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

bool prime[300000];
struct card {
  int p, c, l;
};

bool can(const vector<card> &cards, int k, int thresh) {
  Flow::reset_residual();
  int n = SZ(cards);
  int s = n, t = n + 1;
  vector<vector<int>> g(n + 3);
  int maxone = 0, one = n + 2;
  int sum = 0;
  for (int i = 0; i < n; ++i) if (cards[i].l <= k) {
    if (cards[i].c == 1) {
      uax(maxone, cards[i].p);
      continue;
    }
    sum += cards[i].p;
    if (cards[i].c & 1) {
      g[s].push_back(i);
      g[i].push_back(s);
      Flow::residual[s][i] = cards[i].p;
      for (int j = 0; j < n; ++j) if (cards[i].l <= k && prime[cards[i].c + cards[j].c]) {
        g[j].push_back(i);
        g[i].push_back(j);
        Flow::residual[i][j] = Flow::INF;
      } 
    } else {
      g[t].push_back(i);
      g[i].push_back(t);
      Flow::residual[i][t] = cards[i].p;
    }
  }
  g[s].push_back(one);
  g[one].push_back(s);
  Flow::residual[s][one] = maxone;
  for (int i = 0; i < n; ++i) if (cards[i].c != 1 && cards[i].l <= k && prime[1 + cards[i].c]) {
    g[one].push_back(i);
    g[i].push_back(one);
    Flow::residual[one][i] = Flow::INF;
  }
  sum += maxone;
  int flow = Flow::max_flow(g, s, t);
  return sum - flow >= thresh;
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  memset(prime, true, sizeof prime);
  prime[0] = prime[1] = false;
  for (int i = 2; i < 300000; ++i) if (prime[i]) {
    for (int j = i + i; j < 300000; j += i) prime[j] = false;
  }
  int n, k;
  cin >> n >> k;
  vector<card> cards(n);
  
  for (auto &a: cards) {
    cin >> a.p >> a.c >> a.l;
  }
  int lo = 1, hi = 100001;
  while (lo < hi) {
    int md = (lo + hi) >> 1;
    if (can(cards, md, k)) hi = md;
    else lo = md + 1;
  }
  cout << (lo == 100001 ? -1 : lo) << '\n';

  return 0;
} 
