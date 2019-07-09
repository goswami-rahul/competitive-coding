
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
const int nax = 805;
int dp[3][nax];

int go(int n, int b = 0) {
  if (n < 1) return 0;
  if (n == 1) return b != 0;
  int &g = dp[b][n];
  if (~g) return g;
  vector<bool> has(nax << 1, false);
  if (b == 0) {
    for (int i = 1; i < n; ++i) {
      has[go(i - 1, 0) ^ go(n - i - 1, 1)] = true;
    }
  } else if (b == 1) {
    for (int i = 1; i < n; ++i) {
      has[go(i - 1, 1) ^ go(n - i - 1, 1)] = true;
      has[go(i - 1, 2) ^ go(n - i - 1, 0)] = true;
    }
    has[go(n - 1, 0)] = true;
  } else if (b == 2) {
    for (int i = 1; i < n; ++i) {
      has[go(i - 1, 1) ^ go(n - i - 1, 2)] = true;
    }
    has[go(n - 1, 1)] = true;
  }
  for (g = 0; has[g]; ++g);
  return g;
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int tt;
  cin >> tt;
  memset(dp, -1, sizeof dp);
  while (tt--) {
    int n; cin >> n;
    cout << (go(n) ? "X\n" : "Y\n");
  }
  
  return 0;
} 
