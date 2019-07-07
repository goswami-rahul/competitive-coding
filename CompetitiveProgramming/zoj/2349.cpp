/**
 * We can solve it using dp, dp[i] = longest chain ending at ith string
 * Since order doesn't matter, we will use frequency array rather than strings
 * Each string can be reached by atmost 26 such frquency arrays, each with
 * one count less in exactly one character.
 * We can check for all those frequence arrays and update our dp.
 * To search for the arrays fast, map the positions of frequency arrays
 * to their indices (using std::map in C++). 
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
struct item {
  int len;
  array<int,26> cnt{};
  string str;
};
ostream& operator << (ostream& os, const item &x) {
  vector<int> cnt(ALL(x.cnt));
  return os << cnt << " : " << x.str << endl;
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  while (tt--) {
    bool done = false;
    vector<item> a;
    while (true) {
      string s;
      getline(cin, s);
      if (s.empty()) {
        if (done) break;
        continue;
      }
      done = true;
      item cur;
      cur.len = (int) s.length();
      cur.str = s;
      for (const char &c: s) cur.cnt[c - 'a']++;
      a.push_back(std::move(cur));
    }
    sort(ALL(a), [&] (const item &x, const item &y) {
      return x.len < y.len;
    });
    map<array<int,26>,int> Id;
    const int n = (int) a.size();
    assert(n > 0);
    vector<int> dp(n), where(n);
    int opt = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (a[i].cnt[j] > 0) {
          a[i].cnt[j]--;
          auto it = Id.find(a[i].cnt);
          if (it != Id.end() && uax(dp[i], dp[it->second])) {
            where[i] = it->second;
          }
          a[i].cnt[j]++;
        }
      }
      dp[i]++;
      if (dp[opt] < dp[i]) opt = i;
      Id[a[i].cnt] = i;
    }
    vector<int> ans;
    while (true) {
      ans.push_back(opt);
      if (dp[opt] == 1) break;
      opt = where[opt];
    }
    reverse(ALL(ans));
    for (const int &i : ans) {
      cout << a[i].str << '\n';
    }
    if (tt) cout << '\n';
  }
  
  return 0;
} 
