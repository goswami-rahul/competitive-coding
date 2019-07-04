/**
 * First notice that numbers at even depths, ie, 0th (root), 2nd, .. level
 * doesn't have any effect on the answer, since whenever one player move
 * stones from those levels, second can just move the same stones one more level
 * above to cancel it. Now, the game becomes a normal nim game, with stones
 * at odd levels, so we can simply xor all numbers at odd levels.
 * To answer queries, Maintain, both even and odd level xors  for subtree
 * of each node, and also the parity of the level.
 * Now, when we move the node to some other place, check if new parity has changed,
 * if yes, switch the xor contribution of that node from odd to even, or even to odd.
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
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &c: a) cin >> c;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v; cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> exr(n), oxr(n);
  vector<int> tin(n), tout(n);
  int timer = 0;
  vector<bool> odd(n, false);
  function<void(int,int)> dfs = [&] (int u, int p) {
    tin[u] = timer++;
    for (const int &v: g[u]) if (v != p) {
      odd[v] = odd[u] ^ true;
      dfs(v, u);
      exr[u] ^= oxr[v];
      oxr[u] ^= exr[v];
    }
    exr[u] ^= a[u];
    tout[u] = timer++;
  };
  dfs(0, 0);
  int q; cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    if (tin[u] < tin[v] && tout[v] < tout[u]) {
      cout << "INVALID\n";
    } else {
      int ans = oxr[0];
      if (odd[u] == odd[v]) ans ^= exr[u] ^ oxr[u];
      cout << (ans ? "YES\n" : "NO\n");
    }
  }

  return 0;
} 
