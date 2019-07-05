/**
 * The state of game is determined by the frequencies of add and even numbers.
 * First, check for some corner cases, when 2nd player could remove all
 * odd parities, and some player could remove all even parities.
 * Otherwise, the last player always has the option to modify the parity, 
 * and he is the winner.
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
  
  int n, k, a = 0, b = 0;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x; 
    if (x & 1) ++a; else ++b;
  }
  if (k == n) kek(a & 1 ? "Stannis" : "Daenerys");
  int his = (n - k) / 2, my = n - k - his;
  if (a <= his) kek("Daenerys");
  if (k % 2 == 1 && b <= my) kek("Stannis");
  if (k % 2 == 0 && b <= his) kek("Daenerys");
  kek(my == his ? "Daenerys" : "Stannis");

  return 0;
} 
