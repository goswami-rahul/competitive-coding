/**
 * dp[i][j][k] counts the no. of unique subsequences till  first i characters
 * ending with j, and of length k
 * Maintain, dp within a limit (1e12) to avoid overflow.
 * Take the strings in the set greedily from highest length to lowest length.
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
#define int i64
const int nax = 105;
int dp[nax][28][nax];
int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  dp[0][26][0] = 1;
  const int LIM = 1e12 + 42;
  int best = INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= 26; ++j) {
      for (int p = 0; p <= n; ++p) {
        dp[i][j][p] = dp[i - 1][j][p];
      }
    }
    for (int p = 1; p <= n; ++p) {
      dp[i][s[i - 1] - 'a'][p] = 0;
      for (int u = 0; u <= 26; ++u) {
        dp[i][s[i - 1] - 'a'][p] += dp[i - 1][u][p - 1];
      }
    }
    vector<int> b(n + 1, 0);
    for (int j = 0; j <= 26; ++j) {
      for (int p = 0; p <= n; ++p) {
        uin(dp[i][j][p], LIM);
        b[p] += dp[i][j][p];
      }
    }
    int need = k, cost = 0;
    for (int j = n; ~j; --j) {
      int take = min(need, b[j]);
      need -= take;
      cost += take * (n - j);
    }
    if (need == 0) uin(best, cost);
  }
  kek(best == INF ? -1 : best);
  
  return 0;
}
