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
int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    solve_case();
  }
}
const int Dx[] = {-1, 0, 1, 0};
const int Dy[] = {0, -1, 0, 1};
void solve_case() {
  int n, m; cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  vector<vector<array<pair<int,int>, 4>>> b(n);
  for (auto &v : b) v.resize(m);
  i64 sum = 0;
  for (auto &v : a) for (int &x : v) cin >> x, sum += x;
  i64 ans = sum;
  vector<pair<int,int>> bfs;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int cur = 0;
      for (int k = 0; k < 4; ++k) {
        int x = i + Dx[k], y = j + Dy[k];
        if (0 <= x && x < n && 0 <= y && y < m) {
          b[i][j][k] = {x, y};
          cur += a[x][y] - a[i][j];
        } else {
          b[i][j][k] = {-1, -1};
        }
      }
      if (cur > 0) {
        bfs.emplace_back(i, j);
      }
    }
  }
  while (!bfs.empty()) {
    set<pair<int,int>> cands;
    for (auto &pr : bfs) {
      int x, y; tie(x, y) = pr;
      sum -= a[x][y];
      for (int k = 0; k < 4; ++k) {
        int nx, ny; tie(nx, ny) = b[x][y][k];
        if (~nx) {
          b[nx][ny][k ^ 2] = b[x][y][k ^ 2];
          cands.emplace(nx, ny);
        }
      }
    }
    for (auto &pr : bfs) cands.erase(pr);
    ans += sum;
    bfs = {};
    for (auto &pr : cands) {
      int x, y; tie(x, y) = pr;
      int cur = 0;
      for (int k = 0; k < 4; ++k) {
        int nx, ny; tie(nx, ny) = b[x][y][k];
        if (~nx) {
          cur += a[nx][ny] - a[x][y];
        }
      }
      if (cur > 0) bfs.emplace_back(x, y);
    }
  }
  cout << ans << '\n';
}
