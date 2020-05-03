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
void run();
int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  
  //~ run();
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    solve_case();
  }
}

void run() {
  set<int> s{0};
  int k; cin >> k;
  for (int i = 0; i <= k; ++i) {
    error(i, s);
    set<int> t;
    for (int x : s) {
      t.insert(x - (1 << i));
      t.insert(x + (1 << i));
    }
    swap(s, t);
  }
}
const string no = "IMPOSSIBLE\n";
void solve_case() {
  i64 x, y; cin >> x >> y;
  i64 ox = x, oy = y;
  i64 nx = 0, ny = 0;
  string s;
  i64 pw = 1;
  x = abs(x), y = abs(y);
  while (x > 0 or y > 0) {
    if (x % 2 == y % 2) {
      cout << no;
      return;
    }
    if (x & 1) {
      x >>= 1;
      y >>= 1;
      if (x == 0 && y == 0) {
        s += 'E';
        nx += pw; 
        break;
      }
      if (x % 2 == y % 2) {
        s += 'W';
        nx -= pw;
        ++x;
      } else {
        s += 'E';
        nx += pw;
      }
    } else if (y & 1) {
      y >>= 1;
      x >>= 1;
      if (x == 0 && y == 0) {
        s += 'N';
        ny += pw;
        break;
      }
      if (x % 2 == y % 2) {
        ++y;
        s += 'S';
        ny -= pw;
      } else {
        s += 'N';
        ny += pw;
      }
    }
    pw <<= 1;
  }
  assert (abs(nx) == abs(ox) && abs(ny) == abs(oy));
  if ((ox < 0 && nx > 0) or (ox > 0 && nx < 0)) {
    for (char &c : s) {
      if (c == 'E' or c == 'W') c ^= 'E' ^ 'W';
    }
  }
  if ((oy < 0 && ny > 0) or (oy > 0 && ny < 0)) {
    for (char &c : s) {
      if (c == 'N' or c == 'S') c ^= 'S' ^ 'N';
    }
  }
  cout << s << '\n';
}
