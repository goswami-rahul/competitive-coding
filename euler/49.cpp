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

int32_t main(int argc, char * argv[]) {
  cin.tie(nullptr) -> sync_with_stdio(false);
  (void) argc; (void) argv;
  
  const int N = (int) 1e4;
  array<int, N * 4> p{};
  fill(ALL(p), 1);
  p[0] = p[1] = 0;
  for (int i = 2; i < N; ++i) if (p[i]) {
    for (int j = i + i; j < N; j += i) p[j] = 0;
  }
  for (int i = 1000; i < N; ++i) if (p[i]) {
    if (p[i] && p[i + 3330] && p[i + 3330 + 3330]) {
      string s = to_string(i);
      string t = to_string(i + 3330);
      string u = to_string(i + 3330 * 2);
      sort(ALL(s));
      sort(ALL(t));
      sort(ALL(u));
      if (s == t && t == u) {
        cout << i << i + 3330 << i + 3330 * 2 << endl;
      }
    }
  }
}
