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
  
  int num = 1, den = 1;
  for (int i = 10; i < 100; ++i) {
    for (int j = i + 1; j < 100; ++j) {
      if (i % 10 and j % 10) {
        int ok = 0;
        for (int a : {i % 10, i / 10}) {
          for (int b : {j % 10, j / 10}) {
            ok |= (a * j == b * i && (a ^ (i % 10) ^ (i / 10)) == (b ^ (j % 10) ^ (j / 10)));
          }
        }
        if (ok) num *= i, den *= j;
        if (ok) error(i, j);
      }
    } 
  }
  int g = gcd(num, den);
  error(num, den, g);
  num /= g, den /= g;
  cout << den << endl;
}
