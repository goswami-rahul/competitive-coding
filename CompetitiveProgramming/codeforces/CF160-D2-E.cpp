/*
 * First, use coordinate compression on the ranges, to make all
 * between reasonable ranges. Now, sort the buses and ppl acc. to
 * the time ti.
 * Traverse both of them together in ascending order of time.
 * When person is encountered, insert its Li at position Ri of the
 * Segment Tree. And maintain maximum of Li over range [1, x].
 * When bus is encountered, find the ids of person who take this bus.
 * For this, extract max Li, from the range [1, Rbusi] until
 * Li becomes < than Lbusi.
 * and assign them id of the current bus;  
*/
#include<bits/stdc++.h>
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
  for(unsigned int i = 0; i < v.size(); i++) {
    if(!first) os << ", ";
    os << v[i];
    first = false;
  }
  return os << "]";
}
template<typename T>
inline ostream &operator << (ostream & os,const set<T>& v) {
  bool first = true;
  os << "{";
  for (auto ii = v.begin(); ii != v.end(); ++ii) {
    if(!first) os << ", ";
    os << *ii;
    first = false;
  }
  return os << "}";
}
inline ostream &operator << (ostream & os,const multiset<int>& v) {
  bool first = true;
  os << "{";
  for (auto x: v) {
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
  for (typename map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
    if(!first) os << ", ";
    os << *ii ;
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
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
/***********************************************************************/
struct Node {
  set<pair<int,int>> a;
  pair<int,int> mx;
  Node(): mx({-1,-1}) {};
};
struct SegTree {
  #define li (i + i)
  #define ri (i + i + 1)
  vector<int> ss, ee;
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
  inline void update(int i, int pos, int val, int id) {
    if (ss[i] == ee[i]) {
      assert (ss[i] == pos);
      if (val == -1) {
        t[i].a.erase(prev(t[i].a.end()));
        t[i].mx = (t[i].a.empty() ? make_pair(-1, -1) : *t[i].a.rbegin());
      } else {
        t[i].a.emplace(val, id);
        uax(t[i].mx, make_pair(val, id));
      }
      return;
    }
    update((pos <= ee[li] ? li : ri), pos, val, id);
    t[i].mx = max(t[li].mx, t[ri].mx);
  }
  inline pair<int,int> ask(int i, int qs, int qe) {
    if (qs == ss[i] && qe == ee[i]) { return t[i].mx; }
    if (qe <= ee[li]) { return ask(li, qs, qe); }
    if (qs >= ss[ri]) { return ask(ri, qs, qe); }
    return max(ask(li, qs, ee[li]), ask(ri, ss[ri], qe));
  }
  void update(int pos, int val, int id) {
    return update(1, pos, val, id);
  }
  int ask(int upto) {
    return ask(1, 1, upto).second;
  }
  #undef li
  #undef ri
};

struct item {
  int l, r, t, no;
  bool operator < (const item& rhs) {
    return t < rhs.t;
  }
};
ostream &operator << (ostream & os, item v) {
  return os << "<" << v.l << ", " << v.r << ", " << v.t << ">";
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;
  map<int,int> ff;
  vector<item> a(n), b(m);
  int ptr = 0;
  for (auto& x : a) {
    cin >> x.l >> x.r >> x.t;
    x.no = ptr++;
    ff[x.r]; ff[x.l];
  }
  ptr = 0;
  for (auto& x : b) {
    cin >> x.l >> x.r >> x.t;
    x.no = ptr++;
    ff[x.l]; ff[x.r];
  }
  sort(ALL(a));
  sort(ALL(b));
  ptr = 1;
  for (auto &[k, v]: ff)
    v = ptr++;
  for (auto &x : a) {
    x.l = ff[x.l];
    x.r = ff[x.r];
  }
  for (auto &x : b) {
    x.l = ff[x.l];
    x.r = ff[x.r];
  }
  vector<int> ans(m, -1);
  SegTree seg(ptr);
  int i1 = -1, i2 = 0;
  while (++i1 < n) {
    while (i2 < m && b[i2].t <= a[i1].t) {
      seg.update(b[i2].r, b[i2].l, i2);
      ++i2;
    }
    int id;
    while ((id = seg.ask(a[i1].r)) != -1 && b[id].l >= a[i1].l) {
      seg.update(b[id].r, -1, id);
      ans[b[id].no] = a[i1].no + 1;
    }
  }
  for (int x : ans) cout << x << ' ';
  cout << '\n';
  
  return 0;
}
