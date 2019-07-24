/**
 * Find the diameter endpoints, delete every other leaf pairing it with
 * either one of the endpoint, whichever has more distance.
 * When, all th other leafs are destroyed, start deleting leaf from either
 * end.
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
 
  int n;
  cin >> n;
  if (n == 2) {
    cout << "1\n1 2 2\n";
    return 0;
  }
  vector<vector<int>> g(n);
  vector<int> deg(n, 0);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back(v);
    g[v].push_back(u);
    deg[u]++;
    deg[v]++;
  }
  auto dfs = [&] (int u, int p, int h) {
    auto lam = [&] (int u, int p, int h, const auto &lam) -> pair<int,int> {
      int r = u, my = h;
      for (const int &v: g[u]) if (v != p) {
        int w, his;
        tie(w, his) = lam(v, u, 1 + h, lam);
        if (uax(my, his)) r = w;
      }
      return make_pair(r, my);
    };
    return lam(u, p, h, lam).first;
  };
  vector<int> a(2);
  a[0] = dfs(0, 0, 0);
  a[1] = dfs(a[0], 0, 0);
  vector<vector<int>> dis(2, vector<int>(n, -1));
  for (int i : {0, 1}) {
    vector<int> buf = {a[i]};
    dis[i][a[i]] = 0;
    while (!buf.empty()) {
      int u = buf.back();
      buf.pop_back();
      for (const int &v: g[u]) {
        if (dis[i][v] == -1) {
          dis[i][v] = 1 + dis[i][u];
          buf.push_back(v);
        }
      }
    }
  }
  vector<int> leafs;
  for (int i = 0; i < n; ++i) {
    if (i != a[0] && i != a[1] && deg[i] == 1) {
      leafs.push_back(i);
    }
  }
  i64 opt = 0;
  vector<array<int,3>> ans;
  while (!leafs.empty()) {
    int u = leafs.back();
    leafs.pop_back();
    deg[u]--;
    if (dis[0][u] > dis[1][u]) {
      opt += dis[0][u];
      ans.push_back({a[0], u, u});
    } else {
      opt += dis[1][u];
      ans.push_back({a[1], u, u});
    }
    for (const int &v : g[u]) {
      if (deg[v] > 1) {
        deg[v]--;
        if (deg[v] == 1) {
          leafs.push_back(v);
        }
      }
    }
  }
  int d = dis[0][a[1]];
  while (d > 0) {
    opt += d--;
    ans.push_back({a[0], a[1], a[0]});
    deg[a[0]]--;
    for (const int &v : g[a[0]]) {
      if (deg[v] > 0) {
        deg[v]--;
        a[0] = v;
        break;
      }
    }
  }
  assert (SZ(ans) == n - 1);
  cout << opt << '\n';
  for (auto [a, b, c] : ans) {
    cout << a + 1 << " " << b + 1 << " " << c + 1 << "\n";
  }
  
  return 0;
}
