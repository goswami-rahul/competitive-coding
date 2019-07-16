/**
 * We can maintain number of ways to break even number of edges,
 * and odd number of edges in a subtree, and compute the values
 * for the parent node from its children nodes.
 * Finally, when root node's xor is x, the answer is to break even edges,
 * when root node's xor is 0, the answer is to break odd edges.
 * otherwise 0.
 * Corner case when x = 0.
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
inline int add(int a, int b, int mod = MOD) {
  a += b;
  if (a >= mod) a -= mod;
  return a;
}
inline int sub(int a, int b, int mod = MOD) {
  a -= b;
  if (a < 0) a += mod;
  return a;
}
inline int mul(int a, int b, int mod = MOD) {
  return int((long long) a * b % mod);
}
inline int mpow(int base, long long ex, int mod = MOD) {
  int res = 1;
  while (ex > 0) {
    if (ex & 1) res = mul(res, base, mod);
    base = mul(base, base, mod);
    ex >>= 1;
  }
  return res;
}
struct Info {
  int eve, odd, xr;
};
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, x;
  cin >> n >> x;
  vector<int> a(n);
  for (int &z : a) {
    cin >> z;
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int zeros = 0;
  function<Info(int,int)> dfs = [&] (int u, int p) {
    Info my{1, 0, a[u]};
    for (const int &v : g[u]) if (v != p) {
      auto his = dfs(v, u);
      my.xr ^= his.xr;
      int eve = add(mul(my.eve, his.eve), mul(my.odd, his.odd));
      int odd = add(mul(my.eve, his.odd), mul(my.odd, his.eve));
      my.eve = eve, my.odd = odd;
    }
    if (u == 0) {
      if (x == 0 && my.xr == x) kek(mpow(2, zeros));
      if (my.xr == 0) kek(my.odd);
      if (my.xr == x) kek(my.eve);
      kek(0);
    }
    zeros += my.xr == 0;
    if (my.xr == x) {
      my.odd = add(my.odd, my.eve);
    } else if (my.xr == 0) {
      my.eve = add(my.eve, my.odd);
    }
    return my;
  };
  dfs(0, 0);
  
  return 0;
}
