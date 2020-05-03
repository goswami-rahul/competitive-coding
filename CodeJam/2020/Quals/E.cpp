#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) begin(vec), end(vec)
typedef long long i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
#ifdef Rahul
# define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#else
# define error(...) 42;
#endif
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
int Nerr;
template<typename A> string to_string(A *p) {return to_string(vector<A>(p, p + Nerr));}
void err(istream_iterator<string>) { cerr << endl; }
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << "; "; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
#define Lu(...) [&] (auto &&u) { return __VA_ARGS__; }
#define Luv(...) [&] (auto &&u, auto &&v) { return __VA_ARGS__; }
int const MOD = 1e9 + 7;
i64 const INF = 1e18 + 42;
/***********************************************************************/
void before();
void solve_case();
int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  
  //~ before();
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    solve_case();
  }
}
const int N = 50;
int a[N][N];
int r[N][N];
int c[N][N];
int x[N * N];
int y[N * N];
int o[N * N];
int n, k, m;
int grind(int j = 0) {
  if (j == m) return 1;
  int i = o[j];
  for (int p = 1; p <= n; ++p) {
    if (r[x[i]][p] or c[y[i]][p]) continue;
    r[x[i]][p] = c[y[i]][p] = 1;
    a[x[i]][y[i]] = p;
    if (grind(j + 1)) return 1;
    a[x[i]][y[i]] = 0;
    r[x[i]][p] = c[y[i]][p] = 0;
  }
  return 0;
}
int go(int i = 0, int s = 0, int t = 1) {
  if (s + (n - i) * t > k) return 0;
  if (i == n) {
    if (s == k) return grind();
    return 0;
  }
  for (int p = t; p <= n; ++p) {
    a[i][i] = p;
    r[i][p] = 1;
    c[i][p] = 1;
    if (go(i + 1, s + p, p)) return 1;
    a[i][i] = 0;
    r[i][p] = 0;
    c[i][p] = 0;
  } 
  return 0;
}
//~ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(58);

void solve_case() {
  memset(a, 0, sizeof a);
  memset(r, 0, sizeof r);
  memset(c, 0, sizeof c);
  cin >> n >> k;
  m = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (i ^ j) x[m] = i, y[m] = j, ++m;
  }
  iota(o, o + m, 0);
  if (!go()) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  cout << "POSSIBLE\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << a[i][j] << ' ';
    } cout << '\n';
  }
}
void before() {
}
