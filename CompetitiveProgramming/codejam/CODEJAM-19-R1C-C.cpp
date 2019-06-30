/**
 * Consider a state as a subrectangle of the given rectangle.
 * Each valid move, splits the current state into 2 states (or 1 state)
 * To check if we can win, we can calculate grundy (nimber) of the initial
 * state. To count the number of winning moves, we can add the moves while
 * we calculate grundy.
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
int n, m;
vector<string> a;
vector<int> dp;
struct state {
  int x1, x2, y1, y2;
  int moves;
  int grundy() {
    if (x1 == x2 || y1 == y2) return 0;
    int hash = 0;
    for (int z: {x1, x2, y1, y2}) 
      hash = (hash << 4) | z;
    int &g = dp[hash];
    if (~g) return g;
    vector<int> has(32, false), good_row(16, true), good_col(16, true);
    for (int i = x1; i < x2; ++i)  for (int j = y1; j < y2; ++j) {
      if (a[i][j] == '#') good_row[i] = good_col[j] = false;
    }
    for (int i = x1; i < x2; ++i) if (good_row[i]) {
      state state1(*this), state2(*this);
      state1.x2 = i; state2.x1 = i + 1;
      int ng = state1.grundy() ^ state2.grundy();
      has[ng] = true;
      moves += (ng == 0) * (y2 - y1);
    }
    for (int i = y1; i < y2; ++i) if (good_col[i]) {
      state state1(*this), state2(*this);
      state1.y2 = i; state2.y1 = i + 1;
      int ng = state1.grundy() ^ state2.grundy();
      has[ng] = true;
      moves += (ng == 0) * (x2 - x1);
    }
    for (int i = 0; i < 32; ++i) {
      if (!has[i]) {
        return g = i;
      }
    }
    assert (false);
  }
};


void run() {
  cin >> n >> m;
  a.resize(n);
  dp.assign(1 << 16, -1);
  for (string &s: a) cin >> s;
  state s{0, n, 0, m, 0};
  s.grundy();
  cout << s.moves << '\n';
}
int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt; cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    cout << "Case #" << i << ": ";
    run();
  }
  
  return 0;
}
