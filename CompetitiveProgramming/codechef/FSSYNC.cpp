/**
 * Consider any node in tree, we want to find the probability that this
 * node will be "roll-called". It will only be roll-called when the node
 * comes before every dead node in the path from root to it. Since,
 * the distribution is uniform, the probabilty is exactly 
 * 1 /(1 + no. of dead nodes in the path from root till now)
 * The expected value withput optimization is n, so we subtract these from n.
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

int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    int m; cin >> m;
    vector<int> dead(n, false);
    for (int i = 0; i < m; ++i) {
      int u; cin >> u; --u;
      dead[u] = true;
    }
    double ans = n;
    function<void(int,int,int)> dfs = [&] (int u, int p, int c) {
      ans -= 1.0 / (1 + c);
      for (const int &v: g[u]) {
        if (v != p) dfs(v, u, c + dead[u]);
      }
    };
    dfs(0, 0, 0);
    cout.precision(10);
    cout << fixed << ans << '\n';
  }
  
  return 0;
}
