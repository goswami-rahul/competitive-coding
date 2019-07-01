/**
 * Grundy of game can calculated as xors of grundy of each chain
 * For grundy of each chain, do O(n^2) dp of grundy of the subsegment of
 * range [L, R). Each choice breaks up the segment into smaller segments
 * and thus find their grundy, and take their mex as the current grundy.
 * If the grundy of game is 0, then first player loses.
 * Otherwise, we need to find the first move which leads to winning play.
 * To do this, try every move and check which move makes the total
 * grundy as 0. 
 * To do this fast, store the grundy values of first moves for each chain
 * during initial computation.
 * Also, notice that a move with grundy M is winning move, if 
 * (C ^ M) == G, C is grundy of chain, G is grundy of game
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
int dp[128][128];
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  vector<vector<int>> rings(n);
  int win = 0;
  vector<int> gs;
  vector<vector<int>> values;
  for (auto &ring: rings) {
    int k; cin >> k;
    for (int j = 0; j < k; ++j) {
      int x; cin >> x;
      ring.push_back(x);
    }
    vector<int> cur(101, -1);
    memset(dp, -1, sizeof dp);
    function<int(int,int)> grundy = [&] (int x, int y) {
      if (x == y) return 0;
      int &g = dp[x][y];
      if (~g) return g;
      vector<bool> has(128, false), occ(128, false);
      for (int i = x; i < y; ++i) occ[ring[i]] = true;
      for (int i = 1; i <= 100; ++i) if (occ[i]) {
        int xr = 0;
        int s = x;
        for (int j = x; j <= y; ++j) {
          if (j < y && ring[j] > i && (j == x || ring[j - 1] <= i)) {
            s = j;
          } else if ((j == y || ring[j] <= i) && j > x && ring[j - 1] > i) {
            xr ^= grundy(s, j);
          }
        }
        has[xr] = true;
        if (x == 0 && y == k) cur[i] = xr;
      }
      for (g = 0; has[g]; ++g);
      return g;
    };
    gs.push_back(grundy(0, k));
    values.push_back(std::move(cur));
    win ^= gs.back();
  }
  if (win == 0) {
    cout << "S\n";
    return 0;
  }
  cout << "G\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < SZ(rings[i]); ++j) {
      if ((gs[i] ^ values[i][rings[i][j]]) == win) {
        cout << i + 1 << " " << j + 1 << '\n';
        return 0;
      }
    }
  }
  assert (false);
  return 0;
} 
