#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
 
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string>) {}
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2> buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (const auto e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1000000007;
long long const INF = 1e18;
#define PI 3.14159265358979323846
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

/*
 * 1 + (2^n - 1^n)(2^m - 1^m) + (3^n - 2^n)(3^m - 2^m)
*/
int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  const int nax = 1e6;
  vector<int> fac(nax);
  fac[0] = 1;
  for (int i = 1; i < nax; ++i) {
    fac[i] = mul(i, fac[i - 1]);
  }
  
  int tt; cin >> tt;
  while (tt--) {
    int n, m, k;
    cin >> n >> m >> k; --k;
    const int p = max(n + n, m + m) + 1;
    vector<int> y(p);
    y[0] = 1;
    for (int i = 1; i < p; ++i) {
      y[i] = add(y[i - 1], mul(sub(mpow(i + 1, n), mpow(i, n)), sub(mpow(i + 1, m), mpow(i, m))));
    }
    if (k < p) {
      cout << y[k] << '\n';
      continue;
    }
    int num = 1;
    for (int i = 0; i < p; ++i) {
      num = mul(num, k - i);
    }
    int ans = 0;
    for (int i = 0; i < p; ++i) {
      int cur = mul(num, inv(k - i));
      cur = mul(cur, inv(mul(fac[i], fac[p - i - 1])));
      cur = mul(cur, y[i]);
      if ((p - i - 1) & 1) cur = MOD - cur;
      ans = add(ans, cur);
    }
    cout << ans << '\n';
  }
  
  return 0;
}
