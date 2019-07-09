/**
 * Let dp[i][j] be the number of ways to cut prefix of length i,
 * with last cut aster jth position.
 * To update transitions in O(1), also compute prefix arrays of dp
 * for each i.
 * To compare two prefixes in O(1), precompute LCP array of  each pair
 * of suffixes in O(n^2).
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
const int nax = 5050;
int dp[nax][nax], lcp[nax][nax];
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  string s;
  cin >> s;
  for (int i = n - 1; ~i; --i) {
    for (int j = n - 1; ~j; --j) if (s[i] == s[j]) {
      lcp[i][j] = 1 + lcp[i + 1][j + 1];
    }
  }
  auto small = [&] (int i, int j, int len) {
    return lcp[i][j] < len && s[i + lcp[i][j]] < s[j + lcp[i][j]];
  };
  for (int pre = 1; pre <= n; ++pre) {
    dp[pre][0] = 1;
    for (int i = 1; i < pre; ++i) {
      dp[pre][i] = dp[i][i - 1];
      int len = pre - i;
      int k = i - len;
      if (k >= 0) {
        if (small(k, i, len)) --k;
        if (k >= 0) dp[pre][i] = sub(dp[pre][i], dp[i][k]);
      }
      if (s[i] == '0') dp[pre][i] = 0;
      dp[pre][i] = add(dp[pre][i], dp[pre][i - 1]);
    }
  }
  cout << dp[n][n - 1] << '\n';
  
  return 0;
} 
