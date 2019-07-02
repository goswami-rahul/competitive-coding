/**
 * dp[i] = maximum no. of occurances we can achieve if we put the last
 * occurance ending at position i.
 * For the transitions, we need to precalculate bool array jump, and cumulative maximum of dp
 * jump[len] is true if the prefix of length len is equal of the suffix of length len
 * if the pattern. This can be calculated in O(n^2).
 * Calculate dp with appropiate transition in O(n*m).
 * Total complexity is O(m * max(m, n)).
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
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  string s, t;
  cin >> s >> t;
  int n = SZ(s), m = SZ(t);
  if (m > n) kek(0);
  vector<bool> jump(m);
  for (int len = 1; len < m; ++len) {
    bool ok = true;
    for (int i = len; i < m; ++i) {
      ok &= t[i] == t[i - len];
    }
    jump[len] = ok;
  }
  vector<int> dp(n), dpmax(n);
  for (int i = m - 1; i < n; ++i) {
    bool ok = true;
    for (int j = 0; j < m; ++j) {
      if (ok && jump[j] && dp[i - j] > 0) uax(dp[i], 1 + dp[i - j]);
      ok &= s[i - j] == t[m - j - 1] || s[i - j] == '?';
    }
    if (ok) uax(dp[i], 1 + (i - m >= 0 ? dpmax[i - m] : 0));
    dpmax[i] = max(dp[i], (i > 0 ? dpmax[i - 1] : 0));
  }
  kek(dpmax[n - 1]);

  return 0;
} 
