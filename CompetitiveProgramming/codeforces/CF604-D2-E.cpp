/**
 * First observation, only the parity of k matters, since if two equal
 * piles cancel each other.
 * Now, if k is even, we can notice the pattern for grundy numbers in 
 * small values, which can be proven to be valid for all large values
 * For odd k, we can just find the grundy numbers recursively, keeping in
 * mind that odd values > 3 are 0, so it can be calculated in O(log A).
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
int grundy(int x) {
  if (x == 1) return 1;
  if (x == 2) return 0;
  if (x == 3) return 1;
  if (x & 1) return 0;
  int b = (1 << grundy(x - 1)) | (1 << grundy(x >> 1));
  for (int i = 0;; ++i) if (!(b >> i & 1)) return i; 
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int &z: a) cin >> z;
  int g = 0;
  for (int z: a) {
    if (k & 1) {
      g ^= grundy(z);
    } else {
      if (z < 3) g ^= z;
      else g ^= z % 2 == 0;
    }
  }
  kek(g ? "Kevin" : "Nicky");
  
  return 0;
}
/**
 * even k: 0 1 2 3 4 5 6 7
 *      g: 0 1 2 0 1 0 1
 *  odd k: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 *      g: 0 1 0 1 2 0 2 0 1 0  1  0  1  0  1  0  2  0  1  0  2
**/
