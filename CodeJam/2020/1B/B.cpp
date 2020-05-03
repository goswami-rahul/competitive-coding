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
void solve_case();
int A, B;
int qs = 0;
int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  
  int tt; cin >> tt >> A >>B;
  for (int t = 1; t <= tt; ++t) {
    qs = 0;
    solve_case();
    error(qs);
  }
}

const int M = 1e9;
int ask(int x, int y) {
  if (x < -M or x > M or y < -M or y > M) return 0;
  ++qs;
  cout << x << " " << y << endl;
  string res; cin >> res;
  if (res == "MISS") return 0;
  if (res == "HIT") return 1;
  error(x, y);
  if (res == "CENTER") return -1;
  throw;
}

int run(int x, int y) {
  {
    int t = ask(x, y);
    if (t == 0) return 0;
    if (t == -1) return 1;
  }
  int lo = -M, hi = x;
  while (lo < hi) {
    int md = lo + (hi - lo) / 2;
    int t = ask(md, y);
    if (t == -1) return 1;
    if (t) hi = md;
    else lo = md + 1;
  }
  int lx = lo;
  lo = x, hi = M;
  while (lo < hi) {
    int md = lo + (hi - lo + 1) / 2;
    int t = ask(md, y);
    if (t == -1) return 1;
    if (t) lo = md;
    else hi = md - 1;
  }
  int rx = lo;
  int cx = lx + (rx - lx) / 2;
  lo = -M, hi = y;
  while (lo < hi) {
    int md = lo + (hi - lo) / 2;
    int t = ask(cx, md);
    if (t == -1) return 1;
    if (t) hi = md;
    else lo = md + 1;
  }
  int dy = lo;
  lo = y, hi = M;
  while (lo < hi) {
    int md = lo + (hi - lo + 1) / 2;
    int t = ask(cx, md);
    if (t == -1) return 1;
    if (t) lo = md;
    else hi = md - 1;
  }
  int uy = lo;
  int cy = dy + (uy - dy) / 2;
  for (int i = -5; i <= 5; ++i) {
    for (int j = -5; j <= 5; ++j) {
      if (ask(cx + i, cy + j) == -1) return 1;
    }
  }
  throw;
}
void solve_case() {
  for (int x = -1; x <= 1; ++x) {
    for (int y = -1; y <= 1; ++y) {
      if (run(x * (M / 2), y * (M / 2))) return;
    }
  }
  throw;
}
