/**
 * For each beautiful string, calculate an array a, a[i] = leftmost endpoint
 * of occurances of prefix ending at i of the string in the text.
 * To calculate the array, use prefix function on "string" + "$" + "text"
 * Similarly, calculate array b, b[i] = rightmost endpoint of the suffix
 * starting at i of string in the text.
 * computation of b is similar by reversing the text and the string
 * The string can be seen, if there exists an i such that a[i] < b[i + 1];
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

  string s;
  cin >> s;
  int n = (int) s.size();
  int ans = 0;
  int q; cin >> q;
  while (q--) {
    string w;
    cin >> w;
    int m = (int) w.size();
    string t = w + "$" + s;
    vector<int> pi(n + m + 1);
    for (int i = 1; i < n + m + 1; ++i) {
      int p = pi[i - 1];
      while (p > 0 && t[p] != t[i]) p = pi[p - 1];
      if (t[p] == t[i]) pi[i] = 1 + p;
    }
    vector<int> a(m, MOD);
    for (int i = n + m; i > m; --i) {
      if (pi[i]) a[pi[i] - 1] = i - m - 1;
    }
    t = "";
    for (int i = m - 1; ~i; --i) t += w[i];
    t += '$';
    for (int i = n - 1; ~i; --i) t += s[i];
    pi.assign(n + m + 1, 0);
    for (int i = 1; i < n + m + 1; ++i) {
      int p = pi[i - 1];
      while (p > 0 && t[p] != t[i]) p = pi[p - 1];
      if (t[p] == t[i]) pi[i] = 1 + p;
    }
    vector<int> b(m, -1);
    for (int i = n + m; i > m; --i) {
      if (pi[i]) b[m - pi[i]] = n + m - i;
    }
    assert (is_sorted(ALL(a)));
    assert (is_sorted(ALL(b)));
    bool ok = false;
    for (int i = 0; i < m - 1; ++i) {
      ok |= a[i] < b[i + 1];
    }
    ans += ok;
  }
  kek(ans);
  
  return 0;
}
