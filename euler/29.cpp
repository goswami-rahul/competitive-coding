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
int const MOD = 1e9 + 7;
long long const INF = 1e18 + 42;
/***********************************************************************/

int brute(int n) {
  set<i64> s;
  for (int i = 2; i <= n; ++i) {
    i64 x = i;
    for (int j = 2; j <= n; ++j) {
      x *= i;
      s.insert(x);
    }
  }
  error(SZ(s));
  return SZ(s);
}
int brute2(int n) {
  auto ord = [] (long double x, long double y) {
    return abs(x - y) > 1e-9 && x < y;
  };
  set<long double, decltype(ord)> s(ord);
  for (int i = 2; i <= n; ++i) {
    long double lg = log((long double) i), val = lg;
    for (int j = 2; j <= n; ++j) {
      val += lg;
      s.insert(val);
    }
  }
  return SZ(s);
}
int32_t main(int argc, char * argv[]) {
  cin.tie(nullptr) -> sync_with_stdio(false);
  (void) argc; (void) argv;
  
  int n = (1 < argc ? stoi(argv[1]) : 100);
  
  auto calc = [n] (int k) {
    vector<int> a(k * n + 1);
    for (int i = 1; i <= k; ++i) {
      for (int j = i + i; j <= i * n; j += i) {
        a[j] = 1;
      }
    }
    return accumulate(ALL(a), 0);
  };
  int ans = 0;
  vector<int> c(n + 1);
  for (int i = 2; i <= n; ++i) {
    if (!c[i]) {
      int j = i;
      int pw = 0;
      while (j <= n) {
        assert(!c[j]);
        c[j] = 1;
        j *= i;
        ++pw;
      }
      ans += calc(pw);
    }
  }
  error(ans);
  error(brute2(n));
  //~ assert (ans == brute(n));
}
