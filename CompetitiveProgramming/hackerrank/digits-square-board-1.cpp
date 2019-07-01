/**
 * Solve using Sprague-Grundy theorem, base cases are grundy equals 0
 * for 1x1 board and when all the numbers in the board are prime.
 * Solve recursively to find the grundy for the whole board.
 * First player wins if the grundy number is non-zero
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
int dp[32][32][32][32];
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  ofstream fout(getenv("OUTPUT_PATH"));
  int tt;
  cin >> tt;
  while (tt--) {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto &v: a) for (int &x: v) cin >> x;
    memset(dp, -1, sizeof dp);
    function<int(int,int,int,int)> grundy = [&] (int x1, int x2, int y1, int y2) {
      if (x1 + 1 == x2 && y1 + 1 == y2) return 0;
      int &g = dp[x1][x2][y1][y2];
      if (~g) return g;
      
      g = 0;
      bool prime = true;
      for (int i = x1; i < x2; ++i) for (int j = y1; j < y2; ++j) {
        prime &= (a[i][j] == 2 || a[i][j] == 3 || a[i][j] == 5 || a[i][j] == 7);
      }
      if (!prime) {
        vector<bool> has(128, false);
        for (int i = x1 + 1; i < x2; ++i) 
          has[grundy(x1, i, y1, y2) ^ grundy(i, x2, y1, y2)] = true; 
        for (int i = y1 + 1; i < y2; ++i) 
          has[grundy(x1, x2, y1, i) ^ grundy(x1, x2, i, y2)] = true;
        for (; has[g]; ++g);
      }
      return g;
    };
    fout << (grundy(0, n, 0, n) ? "First" : "Second") << '\n';
  }
  
  return 0;
}
