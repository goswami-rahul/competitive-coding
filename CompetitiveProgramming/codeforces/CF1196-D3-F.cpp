/**
 * if n <= k, we can directly use Floyd-Warshall to get all distances,
 * and choose kth-shortest.
 * otherwise, sort the edges and cosider the component with vertices, that
 * appear in the k smallest edges.
 * Any path among these edges won't exceed the kth smallest path,
 * we can again use Floyd-Warshall on this component, and find kth
 * smallest path
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int randint(int a, int b) {
  return uniform_int_distribution<int>(a, b)(rng);
}
struct edge {
  int u, v, r;
  i64 w;
  bool operator < (const edge &rhs) const {
    return make_pair(w, r) < make_pair(rhs.w, rhs.r);
  }
};
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n, m, k;
  cin >> n >> m >> k;
  if (n <= 512) {
    int s = n;
    vector<vector<i64>> dp(s, vector<i64>(s, INF));
    i64 max_ans = 0;
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      --u; --v;
      dp[u][v] = dp[v][u] = w;
      uax(max_ans, (i64) w);
    }
    for (int i = 0; i < s; ++i) dp[i][i] = 0;
    for (int d = 0; d < s; ++d) {
      for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
          uin(dp[i][j], dp[i][d] + dp[d][j]);
        }
      }
    }
    vector<i64> ds;
    for (int i = 0; i < s; ++i) {
      for (int j = i + 1; j < s; ++j) {
        ds.push_back(dp[i][j]);
      }
    }
    sort(ALL(ds));
    kek(ds[k - 1]);
    
    return 0;
  }
  vector<edge> edges(m);
  for (auto &e: edges) {
    cin >> e.u >> e.v >> e.w;
    e.r = randint(0, (int) 1e9);
  }
  sort(ALL(edges));
  map<int,int> use;
  i64 max_ans = 0;
  for (int i = 0; i < min(k + 10, m); ++i) {
    use[edges[i].u] = -1;
    use[edges[i].v] = -1;
    uax(max_ans, edges[i].w);
  }
  int s = 0;
  for (auto &[_, v] : use) {
    v = s++;
  }
  vector<vector<i64>> dp(s, vector<i64>(s, INF));
  for (const auto &e : edges) {
    if (use.count(e.u) && use.count(e.v)) {
      dp[use[e.u]][use[e.v]] = dp[use[e.v]][use[e.u]] = e.w;
    }
  }
  for (int i = 0; i < s; ++i) dp[i][i] = 0;
  for (int d = 0; d < s; ++d) {
    for (int i = 0; i < s; ++i) {
      for (int j = 0; j < s; ++j) {
        uin(dp[i][j], dp[i][d] + dp[d][j]);
      }
    }
  }
  vector<i64> ds;
  for (int i = 0; i < s; ++i) {
    for (int j = i + 1; j < s; ++j) {
      ds.push_back(dp[i][j]);
    }
  }
  sort(ALL(ds));
  i64 ans = min(max_ans, ds[k - 1]);
  kek(ans);
  
  return 0;
}
