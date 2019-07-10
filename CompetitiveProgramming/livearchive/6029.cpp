/**
 * Let pattern length be m
 * Consider (i - 2)th string as a and (i - 1)th string as b.
 * The number of occurances of pattern in ith string is equal to
 * occurances in a + occurances in b + occurances in c
 * where c = suffix of b of length (m - 1) concat prefix of a of length (m - 1)
 * Now, notice that prefix of every string is same.
 * And suffix of every alternate string is same.
 * Therefore, there are only 2 possible strings c, we can calculate
 * the occurances in those two as inc1 and inc2, and calculate
 * occurances in upto strings of size just greater than m.
 * After that, just add inc1 and inc2 to the counts and update
 * then similar to fibonaccci.
 * To count occurances in O(length), use prefix function.
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
int count(const string &text, const string &pat) {
  string s = pat + "#" + text;
  vector<int> pi(SZ(s));
  int res = 0;
  for (int i = 1; i < SZ(s); ++i) {
    int p = pi[i - 1];
    while (p > 0 && s[p] != s[i]) p = pi[p - 1];
    if (s[p] == s[i]) pi[i] = 1 + p;
    res += i >= SZ(pat) && pi[i] == SZ(pat);
  }
  return res;
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  int tt = 0;
  while (cin >> n) {
    ++tt;
    string pat;
    cin >> pat;
    int m = SZ(pat);
    if (n < 2) {
      cout << "Case " << tt << ": " << (i64) (m == 1 && pat[0] - '0' == n) << '\n';
      continue;
    }
    i64 now = 0;
    string a = "0", b = "1";
    for (int i = 1; i < n; ++i) {
      a = b + a; swap(a, b);
      if (SZ(b) >= m) {
        now = count(b, pat);
        ++i;
        if (i == n) break;
        i64 pre2 = now;
        a = b + a; swap(a, b);
        now = count(b, pat);
        ++i;
        if (i == n) break;
        i64 pre = now;
        a = b + a; swap(a, b);
        now = count(b, pat);
        ++i;
        if (i == n) break;
        i64 inc1 = now - pre - pre2;
        a = b + a; swap(a, b);
        pre2 = pre;
        pre = now;
        now = count(b, pat);
        i64 inc2 = now - pre - pre2;
        for (++i; i < n; ++i) {
          pre += now; swap(pre, now);
          now += inc1;
          swap(inc1, inc2);
        }
      }
    }
    cout << "Case " << tt << ": " << now << '\n';
  }
  
  return 0;
}
