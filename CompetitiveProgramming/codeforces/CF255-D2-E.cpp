/**
 * After one move on a pile, the pile will have less than 1e6 coins.
 * So, first, calculate grundy for all numbers upto 1e6 (bruteforce).
 * Inspecting the grundy numbers, we can observe that the maximum grundy 
 * is 3 in this range. 
 * Therefore, the grundy upto 1e12 can be atmost 4.
 * Now, we can keep cumulative count of each grundy in the range,
 * and calculate grundy of any number < 1e12 in constant time.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef unsigned long long i64;
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
const int nax = 1000000;
const int gax = 5; // max grundy

int cnt[gax][nax];
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  vector<int> g(nax);
  for (int i = 3; i < nax; ++i) {
    double rr = sqrt((double) i), ll = sqrt(rr);
    int r = (int) rr, l = (int) ll;
    if ((r + 1) * (r + 1) <= i) ++r;
    if (l * l * l * l < i) ++l;
    int has = 0;
    for (int j = l; j <= r; ++j) has |= 1 << g[j];
    for (g[i] = 0; has >> g[i] & 1; ++g[i]);
  }
  cnt[g[0]][0]++;
  for (int i = 1; i < nax; ++i) {
    for (int j = 0; j < gax; ++j) 
      cnt[j][i] = cnt[j][i - 1];
    cnt[g[i]][i]++;
  }
  int ans = 0;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    i64 a; cin >> a;
    if (a < nax) {
      ans ^= g[a];
    } else {
      long double rr = sqrt((long double) a), ll = sqrt(rr);
      i64 r = (i64) rr, l = (i64) ll;
      if ((r + 1) * (r + 1) <= a) ++r;
      if (l * l * l * l < a) ++l;
      for (int x = 0;; ++x) {
        if (cnt[x][r] - cnt[x][l - 1] == 0) {
          ans ^= x;
          break;
        }
      }
    }
  }
  cout << (ans ? "Furlo\n" : "Rublo\n");
  
  return 0;
}
/**
 * y < x
 * y^2 <= x <= y^4
**/
