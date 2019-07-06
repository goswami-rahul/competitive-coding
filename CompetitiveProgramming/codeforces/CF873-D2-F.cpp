/**
 * First reverse both strings, now the problem is slightly modified. The
 * forbidden strings are those which begin at the forbidden indices.
 * In other words, any prefix for ith suffix cant be counted if i index is forbidden.
 * Construct the suffix array.
 * Now, calculate the lcp array such that lcp[i] contains longest common prefix
 * of ith and (i + 1)th suffixes in sorted order.
 * Now, for each len in lcp array, find the righmost R and leftmost L suffix,
 * such that min(lcp[L]...lcp[R]) = len. It means the substring of length len appears
 * (R - L + 1) times. Maximize the answer with it.
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
vector<int> suffix_array(string s) {
  s += "$";
  const int ALPHA = 256, n = (int) s.size();
  vector<int> suf(n), cls(s.begin(), s.end());
  iota(ALL(suf), 0);
  for (int len = 0, num_cls = ALPHA; len < n; (len == 0 ? len = 1 : len *= 2)) {
    vector<int> suf_aux(n), new_cls(n), radix(num_cls);
    for (int i = 0; i < n; ++i) {
      suf_aux[i] = suf[i] - len;
      if (suf_aux[i] < 0) suf_aux[i] += n;
      radix[cls[suf_aux[i]]]++;
    }
    for (int i = 1; i < num_cls; ++i) radix[i] += radix[i - 1];
    for (int i = n - 1; ~i; --i) {
      suf[--radix[cls[suf_aux[i]]]] = suf_aux[i];
    } 
    num_cls = 1; new_cls[suf[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (cls[suf[i]] != cls[suf[i - 1]] || cls[suf[i] + len] != cls[suf[i - 1] + len])
        num_cls++;
      new_cls[suf[i]] = num_cls - 1;
    }
    cls = std::move(new_cls);
  }
  for (int i = 1; i < n; ++i) suf[i - 1] = suf[i];
  suf.pop_back();
  return suf;
}
 
vector<int> compute_lcp(const string &s, const vector<int> &suf) {
  const int n = (int) s.size();
  vector<int> rank(n), lcp(n - 1);
  for (int i = 0; i < n; ++i) rank[suf[i]] = i;
  for (int i = 0, k = 0; i < n; ++i, k = max(0, k - 1)) {
    if (rank[i] == n - 1) { k = 0; continue; }
    int j = suf[rank[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
    lcp[rank[i]] = k;
  }
  return lcp;
}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n; cin >> n;
  string s, t; 
  cin >> s >> t;
  reverse(ALL(s));
  reverse(ALL(t));
  auto suf = suffix_array(s);
  auto lcp = compute_lcp(s, suf);
  vector<int> L(n - 1), R(n - 1);
  {
    stack<int> stk;
    for (int i = 0; i < n - 1; ++i) {
      while (!stk.empty() && lcp[stk.top()] >= lcp[i]) stk.pop();
      L[i] = (stk.empty() ? 0 : stk.top() + 1);
      stk.push(i);
    }
  }
  {
    stack<int> stk;
    for (int i = n - 2; ~i; --i) {
      while (!stk.empty() && lcp[stk.top()] >= lcp[i]) stk.pop();
      R[i] = (stk.empty() ? n - 2 : stk.top() - 1);
      stk.push(i);
    }
  }
  i64 ans = 0;
  vector<int> good(n);
  for (int i = 0; i < n; ++i) {
    good[i] = t[suf[i]] == '0';
    if (good[i]) uax(ans, (i64) n - suf[i]);
    if (i > 0) good[i] += good[i - 1];
  }
  for (int i = 0; i < n - 1; ++i) {
    int cnt = 0;
    cnt += good[R[i] + 1];
    if (L[i] > 0) cnt -= good[L[i] - 1];
    uax(ans, (i64) cnt * lcp[i]);
  }
  cout << ans << '\n';
 
  return 0;
} 
`
