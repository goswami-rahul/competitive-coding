/**
 * let dp[i][c] = maximum length prefix of t that can be formed using
 * first i characters of s, using atmost c different parts
 * 2 transitions:
 * dp[i + 1][c] = dp[i][c]
 * and
 * dp[i + pref][c + 1] = dp[i][c] + pref
 * where pref is lcp of suffixes s[i+1..n] and t[dp[i][c]+1...m]
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
string to_string(char c) { return "'" + string(1, c) + "'";}
string to_string(string s) { return '"' + s + '"';}
string to_string(const char* s) { return to_string((string) s);}
template<typename A> string to_string(A);
template<typename A, typename B> string to_string(pair<A, B> p){
  return "(" + to_string(p.first) + ": " + to_string(p.second) + ")";}
template<typename A> string to_string(A v) {bool f = false; string r = "{"; 
  for (auto x: v) {if (f) r += ", "; r += to_string(x); f = true;} return r += "}";}
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
vector<int> suffix_array(string s) {
  s += "!";
  const int ALPHA = 256, n = (int) s.size();
  vector<int> suf(n), cls(s.begin(), s.end());
  iota(suf.begin(), suf.end(), 0);
  for (int len = 0, num_cls = ALPHA; len < n; len ? len <<= 1 : ++len) {
    vector<int> suf_aux(n), new_cls(n), radix(num_cls);
    for (int i = 0; i < n; ++i) {
      suf_aux[i] = suf[i] - len;
      if (suf_aux[i] < 0) suf_aux[i] += n;
      radix[cls[suf_aux[i]]]++;
    }
    for (int i = 1; i < num_cls; ++i) radix[i] += radix[i - 1];
    for (int i = n - 1; ~i; --i) suf[--radix[cls[suf_aux[i]]]] = suf_aux[i];
    num_cls = 1; new_cls[suf[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (cls[suf[i]] != cls[suf[i - 1]] || cls[suf[i] + len] != cls[suf[i - 1] + len]) 
        ++num_cls;
      new_cls[suf[i]] = num_cls - 1;
    }
    cls = std::move(new_cls);
  }
  for (int i = 0; i < n - 1; ++i) suf[i] = suf[i + 1];
  suf.pop_back();
  return suf;
}
// kasai O(n)
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
  
  int n, m, x;
  string s, t;
  cin >> n >> s >> m >> t >> x;
  string aux = s + "R" + t;
  auto suf = suffix_array(aux);
  auto lcp = compute_lcp(aux, suf);
  vector<int> ord(m + n + 1);
  for (int i = 0; i < m + n + 1; ++i)
    ord[suf[i]] = i;
  int sz = SZ(lcp);
  vector<int> tree(sz);
  tree.insert(tree.end(), ALL(lcp));
  assert((int) tree.size() == sz + sz);
  for (int i = sz - 1; i > 0; --i) 
    tree[i] = min(tree[i + i], tree[i + i + 1]);
  auto ask = [&] (int i, int j) {
    j += n + 1;
    i = ord[i], j = ord[j];
    if (i > j) swap(i, j);
    int res = MOD;
    for (i += sz, j += sz; i < j; i /= 2, j /= 2) {
      if (i & 1) uin(res, tree[i++]);
      if (j & 1) uin(res, tree[--j]);
    }
    return res;
  };
  vector<array<int,32>> dp(n << 1);
  for (int i = 0; i < n; ++i) {
    for (int cnt = 0; cnt <= x; ++cnt) {
      if (dp[i][cnt] == m) kek("YES");
      uax(dp[i + 1][cnt], dp[i][cnt]);
      int pref = ask(i, dp[i][cnt]);
      uax(dp[i + pref][cnt + 1], dp[i][cnt] + pref);
    }
  }
  kek(dp[n][x] == m ? "YES" : "NO");
  
  return 0;
}
