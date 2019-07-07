/**
 * Observation: substrings separated with such i which can never be a valid move,
 * are independent to each other.
 * So we can calculate grundy of each substring with streak of palindrome centers
 * and xor them for grundy of game.
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
vector<int> dp;
int grundy(int n) {
  if (n <= 0) return 0;
  int &g = dp[n];
  if (~g) return g;
  set<int> has;
  for (int i = 1; i <= (n + 1) / 2; ++i) {
    has.insert(grundy(i - 2) ^ grundy(n + 1 - i - 2));
  }
  g = 0;
  for (auto it = has.begin();; ++it, ++g) {
    if (it == has.end() || *it != g) return g;
  }
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  string s;
  cin >> s;
  const int n = SZ(s);
  dp.assign(n, -1);
  int g = 0;
  vector<int> inds, cnts;
  for (int i = 0, cnt = 0; i < n; ++i) {
    if (i > 0 && i + 1 < n && s[i - 1] == s[i + 1]) {
      ++cnt;
    } else if (cnt > 0) {
      inds.push_back(i - cnt);
      cnts.push_back(cnt);
      g ^= grundy(cnt);
      cnt = 0;
    }
  }
  if (g == 0) kek("Second");
  cout << "First\n";
  for (int i = 0; i < SZ(inds); ++i) {
    for (int j = 1; j <= cnts[i]; ++j) {
      if ((grundy(cnts[i]) ^ grundy(j - 2) ^ grundy(cnts[i] + 1 - j - 2)) == g) {
        kek(inds[i] + j);
      }
    }
  }
 
  return 0;
} 
