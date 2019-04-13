/*
 * First traverse array from left to right and considering current element
 * as maximum, Apply all the segments that are to the left of current
 * element, and maintain a minimum over the left part.
 * Update the answer wuth current - minimum at each element.
 * Do the same for right to left traversal.
 */
#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
//~ #include <ext/pb_ds/assoc_container.hpp>
//~ #include <ext/pb_ds/tree_policy.hpp>
//~ template<typename T, typename V = __gnu_pbds::null_type>
//~ using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()

#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
using namespace std;
 
using i64 = long long int;
template <typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template <typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
 
void err(__attribute__((unused)) istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl;
  err(++it, args...);
}
template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& buf) {
  return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
  bool first = true;
  os << "[";
  for (const auto &e: v) {
    if(!first) os << ", ";
    os << e;
    first = false;
  }
  return os << "]";
}
template<typename T>
inline ostream &operator << (ostream & os, multiset<T>& v) {
  bool first = true;
  os << "{";
  for (auto ii = v.begin(); ii != v.end(); ++ii) {
    if(!first) os << ", ";
    os << *ii;
    first = false;
  }
  return os << "}";
}
template<typename T>
inline ostream &operator << (ostream & os,const unordered_set<T>& v) {
  bool first = true;
  os << "{";
  for (const auto &x : v) {
    if(!first) os << ", ";
    os << x;
    first = false;
  }
  return os << "}";
}
template<typename T1, typename T2>
inline ostream &operator << (ostream & os,const map<T1, T2>& v) {
  bool first = true;
  os << "{";
  for (const auto &e : v) {
    if(!first) os << ", ";
    os << e;
    first = false;
  }
  return os << "}";
}
template<typename T>
ostream &operator << (ostream & os,const vector<vector<T>>& v) {
  for (auto &u: v) os << '\n' << u;
  return os;
}
template<typename T>
void finish(T ans) {cout << ans << '\n'; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18 + 100LL;
#define PI 3.14159265358979323846
/***********************************************************************/
signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  if (n == 1) finish("0\n0");
  vector<int> a(n);
  for (int &e: a) cin >> e;
  vector<pair<pair<int,int>,int>> b(m);
  int p = 0;
  for (auto &[x, i]: b)
    cin >> x.first >> x.second, --x.first, --x.second, i = p++;
  sort(ALL(b), [] (auto x, auto y) {
    return x.first.second < y.first.second;
  });
  int ans = -MOD, mn;
  vector<int> s;
  p = 0, mn = MOD;
  auto ac = a;
  for (int i = 0; i < n; ++i) {
    while (p < m && b[p].first.second < i) {
      for (int j = b[p].first.first; j <= b[p].first.second; ++j) {
        ac[j]--;
        uin(mn, ac[j]);
      }
      ++p;
    }
    if (i > 0) uin(mn, ac[i - 1]);
    if (uax(ans, a[i] - mn)) {
      s.clear();
      for (int j = 0; j < p; ++j) {
        s.push_back(b[j].second);
      }
    }
  }
  sort(ALL(b)); reverse(ALL(b));
  p = 0;
  ac = a; mn = MOD;
  for (int i = n - 1; i >= 0; --i) {
    while (p < m && b[p].first.first > i) {
      for (int j = b[p].first.first; j <= b[p].first.second; ++j) {
        ac[j]--;
        uin(mn, ac[j]);
      }
      ++p;
    }
    if (i < n - 1) uin(mn, ac[i + 1]);
    if (uax(ans, a[i] - mn)) {
      s.clear();
      for (int j = 0; j < p; ++j) {
        s.push_back(b[j].second);
      }
    }
  }
  cout << ans << '\n' << SZ(s) << '\n';
  for (int x: s) cout << x + 1 << ' ';
  cout << '\n';
  
  return 0;
}
