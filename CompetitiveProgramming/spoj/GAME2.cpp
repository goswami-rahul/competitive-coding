/**
 * First player wins when the count of the maximum number is odd.
 * First, notice that when the maximum's count is odd, you can always 
 * play a move such that new maximum's count is even (or play the last move
 * and win the game).
 * And when the maximum's count is even, there is no choice but to make
 * the maximum's count odd again.
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
  
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    map<int,int> cnt;
    for (int i = 0; i < n; ++i) {
      int x; cin >> x;
      cnt[x]++;
    }
    cnt.erase(0);
    assert(!cnt.empty());
    int mx = cnt.rbegin()->first, mxcnt = cnt[mx];
    if (mxcnt == 1) {
      auto it = prev(cnt.end());
      if (it == cnt.begin()) cout << 1;
      else {
        --it;
        if (it->second & 1) cout << 1;
        else cout << it->first;
      }
    } else if (mxcnt & 1) {
      cout << (i64) mxcnt * mx;
    } else {
      cout << 0;
    }
    cout << '\n';
  }
  return 0;
} 
