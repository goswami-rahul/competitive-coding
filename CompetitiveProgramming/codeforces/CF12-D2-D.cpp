/* First sort wrt to first attribute, descending order.
 * Now, normalize the values of the 2nd attribute in range [1, n]
 * and create a segment tree (or BIT), that supports
 * point updates and max in range.
 * Traverse the sorted values, update the position at 2nd att.
 * with the value of its 2rd att.
 * Ask for maximum value, until now, in the range [2nd att., n]
 * if it is > current 3rd att., add this to answer.
*/
#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
using namespace std;
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()

using ll = long long int;
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
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/

struct SegTree {
  #define li (i + i)
  #define ri (i + i + 1)
  vector<int> ss, ee;
  using Node = int;
  vector<Node> t;
  SegTree(int n): ss(n << 2), ee(n << 2), t(n << 2) {
    build(1, 1, n);
  }
  void build(int i, int l, int r) {
    ss[i] = l, ee[i] = r;
    if (l == r) { return; }
    int m = (l + r) >> 1;
    build(li, l, m); build(ri, m + 1, r);
  }
  inline void update(int i, int pos, int val) {
    if (ss[i] == ee[i]) {
      uax(t[i], val);
      return;
    }
    update((pos <= ee[li] ? li : ri), pos, val);
    t[i] = max(t[li], t[ri]);
  }
  inline Node ask(int i, int qs, int qe) {
    if (qs == ss[i] && qe == ee[i]) { return t[i]; }
    if (qe <= ee[li]) { return ask(li, qs, qe); }
    if (qs >= ss[ri]) { return ask(ri, qs, qe); }
    return max(ask(li, qs, ee[li]), ask(ri, ss[ri], qe));
  }
  void update(int pos, int val) {
    return update(1, pos, val);
  }
  i64 ask(int L, int R) {
    return ask(1, L, R);
  }
  #undef li
  #undef ri
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(3));
  map<int,int> f; int ptr = 0;
  for (int j = 0; j < 3; ++j) {
    for (int i = 0; i < n; ++i) {
      cin >> a[i][j];
      if (j == 1) f[a[i][j]];
    }
  }
  for (auto &[k, v]: f) v = ++ptr;
  for (auto &x: a) x[1] = f[x[1]];
  sort(a.rbegin(), a.rend());
  
  SegTree seg(ptr);
  vector<vector<int>> todo;
  int last = MOD, ans = 0;
  for (const auto &x: a) {
    if (x[0] < last) {
      for (const auto &y: todo) {
        seg.update(y[1], y[2]);
      }
      todo.clear();
    }
    todo.push_back(x);
    ans += (x[1] < ptr && x[2] < seg.ask(x[1] + 1, ptr));
    last = x[0];
  }
  cout << ans << '\n';
    
  return 0;
}
