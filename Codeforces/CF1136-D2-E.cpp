/*
 * Similar idea from -  https://codeforces.com/blog/entry/65905
 * We can notice that some values are always added
 * to a element at every position of "a".
 * We can subtract those "excess" from "a" i.e.
 * sum of "k" [1, i - 1]
 * and maintain a segment tree with these values.
 * For queries, answer adds up segment tree in range +
 * the total excess "k" values in that range.
 * For updates, find the new value to be set (i.e. a[x] + y)
 * Now set this value for all elements in range
 * [x, (rightmost pos with value < a[x] + y)]
 * To find the rightmost such position, also maintain minimum for each segment.
 */
#include <bits/stdc++.h>
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
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/
struct Node {
  i64 sum, lz, mn;
  Node(): sum(0), lz(-MOD), mn(MOD) {};
  friend Node operator + (const Node &lhs, const Node &rhs) {
    Node node;
    node.sum = lhs.sum + rhs.sum;
    node.mn = min(lhs.mn, rhs.mn);
    return node;
  };
  friend ostream &operator << (ostream &os, const Node &p) {
    return os << "<" << p.sum << ", " << p.lz << ", " << p.mn << ">";
  }
};
struct SegTree {
  #define li (i + i)
  #define ri (i + i + 1)
  vector<int> ss, ee;
  vector<Node> t;
  SegTree(int n, auto& a, auto& k): ss(n << 2), ee(n << 2), t(n << 2) {
    build(1, 1, n, a, k);
  }
  void build(int i, int l, int r, auto& a, auto& k) {
    ss[i] = l, ee[i] = r;
    if (l == r) { t[i].sum = t[i].mn = a[l - 1] - k[l]; return; }
    int m = (l + r) >> 1;
    build(li, l, m, a, k); build(ri, m + 1, r, a, k);
    t[i] = t[li] + t[ri];
  }
  void debug(int i = 1) {
    auto nn = make_pair(make_pair(ss[i], ee[i]), t[i]);
    error(nn);
    if (ss[i] == ee[i]) { return; }
    debug(li); debug(ri);
  }
  inline void push(int i) {
    if (t[i].lz == -MOD) return;
    t[i].mn = t[i].lz;
    t[i].sum = t[i].lz * (ee[i] - ss[i] + 1);
    if (ss[i] < ee[i]) {
      t[li].lz = t[i].lz;
      t[ri].lz = t[i].lz;
    }
    t[i].lz = -MOD;
  }
  inline void update(int i, int us, int ue, i64 a) {
    if (us <= ss[i] && ee[i] <= ue) {
      t[i].lz = a;
      push(i); return;
    }
    push(i);
    if (ue < ss[i] || ee[i] < us) { return; }
    update(li, us, ue, a); update(ri, us, ue, a);
    t[i] = t[li] + t[ri];
  }
  inline int find(int i, i64 a) {
    push(i);
    if (ss[i] == ee[i]) { return ss[i]; }
    push(li); push(ri);
    if (t[ri].mn >= a) { return find(li, a); }
    else { return find(ri, a);}
  }
  inline i64 ask(int i, int qs, int qe) {
    push(i);
    if (qs == ss[i] && qe == ee[i]) { return t[i].sum; }
    if (qe <= ee[li]) { return ask(li, qs, qe); }
    if (qs >= ss[ri]) { return ask(ri, qs, qe); }
    return ask(li, qs, ee[li]) +
      ask(ri, ss[ri], qe);
  }
  void update(int L, int R, i64 val) {
    return update(1, L, R, val);
  }
  i64 ask(int L, int R) {
    return ask(1, L, R);
  }
  int find(i64 x) {
    return find(1, x);
  }
  #undef li
  #undef ri
};

signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<i64> a(n), k(n + 1);
  for (i64 &z: a) cin >> z;
  for (int i = 2; i <= n; ++i) {
    cin >> k[i];
    k[i] += k[i - 1];
  }
  SegTree seg(n, a, k);
  for (int i = 2; i <= n; ++i) {
    k[i] += k[i - 1];
  }
  //~ seg.debug();
  int q; cin >> q;
  while (q--) {
    char c;
    int x, y;
    cin >> c >> x >> y;
    if (c == '+') {
      i64 val = seg.ask(x, x);
      int r = seg.find(val + y);
      seg.update(x, r, val + y);
    } else {
      cout << seg.ask(x, y) + k[y] - k[x - 1] << '\n';
    }
  }
  
  return 0;
}
