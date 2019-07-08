/**
 * Build the suffix array and the LCP array of consecutive suffixes in sorted order.
 * Solve the query for "sum of lcp of all pairs".
 * sort the suffixes in the sorted order, and maintain sums of minimum
 * of LCP range considering current suffix as the rightmost endpoint.
 * Use RMQ for range minimum, such as Segment tree.
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
  const int n = (int) s.size(), ALPHA = 256;
  vector<int> suf(n), cls(ALL(s));
  iota(ALL(suf), 0);
  for (int len = 0, m = ALPHA; len < n; len += max(len, 1)) {
    vector<int> aux(n), ncls(n), radix(m);
    for (int i = 0; i < n; ++i) {
      aux[i] = suf[i] - len;
      if (aux[i] < 0) aux[i] += n;
      radix[cls[aux[i]]]++;
    }
    for (int i = 1; i < m; ++i) radix[i] += radix[i - 1];
    for (int i = n - 1; ~i; --i) suf[--radix[cls[aux[i]]]] = aux[i];
    ncls[suf[0]] = 0; m = 1;
    for (int i = 1; i < n; ++i) {
      if (cls[suf[i]] != cls[suf[i - 1]] || cls[suf[i] + len] != cls[suf[i - 1] + len])
        m++;
      ncls[suf[i]] = m - 1;
    }
    cls = std::move(ncls);
  }
  for (int i = 0; i < n - 1; ++i) suf[i] = suf[i + 1];
  suf.pop_back();
  return suf;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  auto suf = suffix_array(s);
  vector<int> lcp(n - 1);
  vector<int> order(n);
  for (int i = 0; i < n; ++i) order[suf[i]] = i;
  for (int i = 0, k = 0; i < n; ++i, k = max(0, k - 1)) {
    if (order[i] == n - 1) {k = 0; continue; }
    int j = suf[order[i] + 1];
    for (; i + k < n && j + k < n && s[i + k] == s[j + k]; ++k);
    lcp[order[i]] = k;
  }
  vector<int> tree(n << 1, MOD);
  for (int i = 2 * n - 2; i > 0; --i) {
    if (i < n) tree[i] = min(tree[i + i], tree[i + i + 1]);
    else tree[i] = lcp[i - n];
  }
  auto calc = [&] (vector<int> &a) {
    sort(ALL(a), [&] (int i, int j) {
      return order[i] < order[j];
    });
    i64 res = 0;
    vector<i64> dp(SZ(a) - 1);
    stack<pair<int,int>> lft;
    for (int i = 0; i < SZ(a) - 1; ++i) {
      int len = n - a[i];
      for (int l = order[a[i]] + n, r = order[a[i + 1]] + n; l <  r; l /= 2, r /= 2) {
        if (l & 1) uin(len, tree[l++]);
        if (r & 1) uin(len, tree[--r]);
      }
      while (!lft.empty() && lft.top().first > len) lft.pop();
      int k = (lft.empty() ? -1 : lft.top().second);
      dp[i] = (i64) (i - k) * len;
      if (k > -1) dp[i] += dp[k];
      res += dp[i];
      lft.emplace(len, i);
    }
    return res;
  };
  while (q--) {
    int k, l;
    cin >> k >> l;
    vector<int> a(k), b(l), c;
    for (int &z: a) cin >> z, c.push_back(--z);
    for (int &z: b) cin >> z, c.push_back(--z);
    cout << calc(c) - calc(a) - calc(b) << '\n';
  }
 
  return 0;
} 
