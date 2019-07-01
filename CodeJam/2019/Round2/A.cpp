#include <bits/stdc++.h>
using namespace std;
typedef long long int i64;
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
 
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(__attribute__((unused)) istream_iterator<string> it) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2>& buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1000000007;
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/

void test_case() {
  
  int n;
  cin >> n;
  vector<pair<int,int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }
  set<pair<int,int>> up, dn;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int x1 = a[i].first;
      int x2 = a[j].first;
      int y1 = a[i].second;
      int y2 = a[j].second;
      if (x2 < x1 && y2 > y1) {
        int num = y2 - y1;
        int den = x1 - x2;
        int g = __gcd(num, den);
        up.emplace(num / g, den / g);
      }
      if (x2 > x1 && y2 < y1) {
        int num = y1 - y2;
        int den = x2 - x1;
        int g = __gcd(num, den);
        up.emplace(num / g, den / g);
      }
    }
  }
  int ans = SZ(up) + 1;
  cout << ans << '\n';
  
  return;
}

int32_t main() {

  ios_base::sync_with_stdio(false); cin.tie(nullptr);

  int tt = 1;
  cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    cout << "Case #" << i << ": ";
    test_case();
  }
  
  return 0;
}
