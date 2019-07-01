#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef long long i64;
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
void run() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  int ans = 0;
  int mn = 0, cur = 0;
  for (int i = n - 1; ~i; --i) {
    if (s[i] == 'B') {
      if (cur - mn < k) {
        cur++;
      } else {
        cur--;
        ans = add(ans, mpow(2, i + 1));
        s[i] = 'A';
      }
    } else {
      cur--;
    }
    uin(mn, cur);
  }
  cout << ans << '\n';
  error(s);
}
int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    cout << "Case #" << i << ": ";
    run();
  }
   
  return 0;
}
