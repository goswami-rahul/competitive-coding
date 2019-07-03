/**
 * First, create the suffix array of the string.
 * Now, the shortest string is the prefix of length 1 of the first suffix 
 * in the suffix array.
 * The second shortest substring will be the prefix of length 1 of the
 * next suffix in the array if the first and second prefix of length 1 are same
 * Otherwise, we keep taking the all the prefixes of the current suffix,
 * then continue with the next suffix, considering only those prefixes which 
 * have not beem used before.
 * The general idea is to use prefixes of length 1 of current smallest suffix,
 * and upto the next suffixes till which the prefix of length 1 is same.
 * Then with prefixes of length 2, 3, 4...
 * Keep an array used[i], which denotes the number of prefixes used
 * from the ith sorted suffix.
 * We can move to the next smallest substring in this way in O(1).
 * Thus overall complexity is O(m + building suffix array), which in my implementation
 * is O(m + n log n). 
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

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  string s;
  cin >> s;
  int n = (int) s.size();
  int k; cin >> k;
  if (2 * k > (i64) n * (n + 1)) kek("No such line.");
  auto suf = suffix_array(s);
  vector<int> used(n, 0);
  int now = 0, last = -1;
  while (k--) {
    if (used[now] == n - suf[now]) {
      now++; last = -1;
    }
    assert (used[now] != n - suf[now]);
    if (now + 1 < n && used[now] == used[now + 1] && s[suf[now] + used[now]] == s[suf[now + 1] + used[now + 1]]) {
        if (last == -1) last = now;
        used[now]++;
        if (k == 0) kek(s.substr(suf[now], used[now]));
        now++;
    } else {
      used[now]++;
      if (k == 0) kek(s.substr(suf[now], used[now]));
      if (last != -1) now = last;
    }
  }

  return 0;
} 
