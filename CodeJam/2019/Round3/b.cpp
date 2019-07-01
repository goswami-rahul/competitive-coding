#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
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
int const MOD = 1000000007;
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/

void test_case() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &z: a) cin >> z;
  vector<vector<i64>> L(n), R(n);
  for (int k = 0; k < n; ++k) {
    int cur = a[k];
    L[k].push_back(0);
    for (int i = k + 1; i < n; ++i) {
      L[k].push_back(L[k].back());
      if (a[i] >= cur) {
        cur = a[i];
      } else {
        L[k].back() += cur - a[i];
      }
    }
  }
  for (int k = 0; k < n; ++k) {
    int cur = a[k];
    R[k].push_back(0);
    for (int i = k - 1; i >= 0; --i) {
      R[k].push_back(R[k].back());
      if (a[i] >= cur) {
        cur = a[i];
      } else {
        R[k].back() += cur - a[i];
      }
    }
  }
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    int k = i;
    for (int r = i + 2; r < n; ++r) {
      while (k + 1 < r && L[i][k - i] + R[r][r - k - 1] >= L[i][k + 1 - i] + R[r][r - k - 2])
        ++k;
      i64 cost = L[i][k - i] + R[r][r - k - 1];
      ans += cost;
      ans %= MOD;
    }
  }
  cout << ans << '\n';
}

int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    test_case();
  }
  
  return 0;
}
