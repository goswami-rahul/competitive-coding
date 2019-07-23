/**
 * We can compute the prefix function for strings while doing dfs,
 * but it can be quite slow at worst, by recomputing same states.
 * We can precompute the prefix function automata for the given string,
 * since we know that pi value can never exceed length of pattern.
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
  vector<vector<int>> g(n);
  vector<string> a(n);
  for (int i = 1; i < n; ++i) {
    int v;
    cin >> v >> a[i]; --v;
    g[v].push_back(i);
  }
  string s;
  cin >> s;
  int m = (int) s.size();
  s += "#";
  vector<int> pi(m + 1);
  vector<array<int,256>> aut(m + 1);
  for (int i = 1; i < m + 1; ++i) {
    int p = pi[i - 1];
    while (p > 0 && s[i] != s[p]) p = pi[p - 1];
    pi[i] = p + (s[i] == s[p]);
  }
  for (int i = 0; i < m + 1; ++i) {
    for (char c = 'a'; c <= 'z'; c++) {
      if (i > 0 && c != s[i]) aut[i][c] = aut[pi[i - 1]][c];
      else aut[i][c] = i + (c == s[i]);
    }
  }
  int ans = 0;
  function<void(int,int)> dfs = [&] (int u, int cur_pi) {
    for (char c : a[u]) {
      cur_pi = aut[cur_pi][c];
      ans += cur_pi == m;
    }
    for (const int &v: g[u]) dfs(v, cur_pi);
  };
  dfs(0, 0);
  cout << ans << '\n';
  
  return 0;
}
