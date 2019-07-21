/**
 * First, check if the graph is strongly connected.
 * The perform a dfs traversal of graph, marking each vertex as visiting, or
 * visited. When you arrive at an edge which goes to a vertex, which has
 * already completed, return false. If such edge doesn't exist, then
 * it is a cactus.
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
vector<vector<int>> g;
vector<int> s, p, tin;
int timer, num_c;
void dfs(int u) {
  s.push_back(u);
  p.push_back(u);
  tin[u] = timer++;
  for (const int &v : g[u]) {
    if (tin[v] == -1) {
      dfs(v);
    } else {
      while (!p.empty() && tin[p.back()] > tin[v]) {
        p.pop_back();
      }
    }
  }
  if (p.back() == u) {
    num_c++;
    p.pop_back();
    while (!p.empty()) {
      int v = p.back();
      p.pop_back();
      if (v == u) break;
    }
  }
}
vector<int> vis;
bool dfs2(int u) {
  vis[u] = 1;
  for (const int &v: g[u]) {
    if (vis[v] == 1) {
      continue;
    } else if (vis[v] == 2) {
      return false;
    } else {
      if (!dfs2(v)) return false;
    }
  }
  vis[u] = 2;
  return true;
}

int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m;
    cin >> n >> m;
    g.assign(n, vector<int>());
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
    }
    num_c = 0; timer = 0;
    tin.assign(n, -1);
    s.clear(); p.clear();
    dfs(0);
    bool scc = num_c == 1;
    for (int i = 0; i < n && scc; ++i) {
      scc &= tin[i] != -1;
    }
    if (!scc) {
      cout << "NO\n";
      continue;
    }
    vis.assign(n, 0);
    cout << (dfs2(0) ? "YES\n" : "NO\n");
  }
    
  return 0;
}
/**
 * 0 1
 * 1 2
 * 2 3
 * 3 1
 * 3 0
**/
