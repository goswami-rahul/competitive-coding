/**
 * denote the dolls by (l, r) ranges representing (in, out)
 * sort all the dolls by r,
 * process them in this order, for each doll - find the closest r to the
 * left of current doll's l, using binry search
 * Find the count of minimum (l - r)s of all dolls, whose r is to the left 
 * of current doll's l.
 * Add the minimum with current doll's (l - r), and insert it at its position.
 * For the queries and insertions, use Fenwick tree or segment tree
 * with data (min, freq).
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
template<typename A> string to_string(vector<vector<A>> v) {string r; 
  for (auto x: v) r += "\n" + to_string(x); return r;}
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
inline void adds(int &a, int b, int mod = MOD) {
  a += b; if (a >= mod) a -= mod;
}
struct doll_t {
  int s, t;
};
struct node_t {
  int val, freq;
  node_t() : val(MOD), freq(1) {}
  node_t& operator += (const node_t &rhs) {
    if (val == rhs.val) adds(freq, rhs.freq);
    else if (rhs.val < val) *this = rhs;
    return *this;
  }
};

int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n; cin >> n;
  vector<doll_t> a(n);
  int maxs = -1;
  for (auto &d: a) {
    cin >> d.t >> d.s;
    uax(maxs, d.s);
  }
  sort(ALL(a), [] (const doll_t& x, const doll_t &y) {
    return x.t < y.t;
  });
  node_t ans;
  vector<node_t> fen(n + 1);
  vector<int> maxin;
  int ptr = 0;
  for (const doll_t &d : a) {
    int r = (int) (upper_bound(ALL(a), d.s, [] (int x, const doll_t &y) {
      return x < y.t;
    }) - a.begin());
    node_t res;
    for (; r > 0; r -= r & -r)
      res += fen[r];
    if (d.t > maxs) {
      res.val += d.s;
      ans += res;
    } else {
      if (res.val == MOD) res.val = 0;
      res.val += d.s - d.t;
      for (int i = ptr + 1; i <= n; i += i & -i)
        fen[i] += res;
    }
    maxin.push_back(d.s);
    if (ptr > 0) uax(maxin.back(), maxin[ptr - 1]);
    ptr++;
  }
  kek(ans.freq);
  
  return 0;
}
