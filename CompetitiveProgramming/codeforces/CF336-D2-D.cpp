/**
 * We can solve the problem recursively.
 * First, notice that answer of solve(n, m, g) when g = 1,
 * can be obtained by subtracting for g = 0 and subtracting from all
 * possible strings .i.e choose(n + m, n)
 * When solving for g = 0, all strings starting with 1 are answer, plus
 * those strings starting with 0, whose answer for next char is 1.
 * So, we put decrease number of zeroes by one, solve for g = 1.
 * We can see that we always decrease number of zeroes, thus we recurse
 * at most O(n) times.
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
inline int add(int a, int b, int mod = MOD) {
  a += b;
  if (a >= mod) a -= mod;
  return a;
}
inline int sub(int a, int b, int mod = MOD) {
  a -= b;
  if (a < 0) a += mod;
  return a;
}
inline int mul(int a, int b, int mod = MOD) {
  return int((long long) a * b % mod);
}
inline int mpow(int base, long long ex, int mod = MOD) {
  int res = 1;
  while (ex > 0) {
    if (ex & 1) res = mul(res, base, mod);
    base = mul(base, base, mod);
    ex >>= 1;
  }
  return res;
}
inline int inv(int a, int mod = MOD) {
  return mpow(a, mod - 2, mod);
}
vector<int> fac, ifac;
inline int ncr(int n, int r) {
  if (n < r || r < 0) return 0;
  return mul(fac[n], mul(ifac[n - r], ifac[r]));
}
void prepare_factorial(int nax = 1e6 + 10) {
  fac.resize(nax);
  ifac.resize(nax);
  fac[0] = 1;
  for (int i = 1; i < nax; ++i) fac[i] = mul(i, fac[i - 1]);
  ifac[nax - 1] = inv(fac[nax - 1]);
  for (int i = nax - 1; i > 0; --i) ifac[i - 1] = mul(i, ifac[i]);
}

int go(int nz, int no, int g) {
  if (nz + no == 1) return g == no;
  if (nz == 0) return g == 0;
  if (g == 1) return sub(ncr(nz + no, nz), go(nz, no, 0));
  return add(ncr(nz + no - 1, nz), go(nz - 1, no, 1));
  
}
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  prepare_factorial(2e5 + 42);
  int n, m, g;
  cin >> n >> m >> g;
  cout << go(n, m, g) << '\n';
    
  return 0;
}
