/*
 * Build a segment with lazy propogation. Each node conatins the sum,
 * and the lazy parameters are a and d.
 * a - start term of AP
 * d - difference of AP
 * when splitting a and d into 2 children, left child gets same values
 * right child gets a = a + (size of left child) * d, and d remains same.
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
inline ostream &operator << (ostream & os,const multiset<pair<int,int>>& v) {
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
    return os << "}";
  }
  return os;
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
  i64 sum, lza, lzd;
  Node(): sum(), lza(), lzd() {};
};
Node operator + (const Node &lhs, const Node &rhs) {
  Node node;
  node.sum = lhs.sum + rhs.sum;
  return node;
};
ostream &operator << (ostream & os, Node v) {
  return os << "<" << v.sum << ", " << v.lza << ", " << v.lzd << ">";
}
struct SegTree {
  vector<int> st, en;
  vector<Node> t;
  SegTree(int n): st(n << 2), en(n << 2), t(n << 2) {
    build(1, 1, n);
  }
  void build(int i, int ss, int ee) {
    st[i] = ss, en[i] = ee;
    if (ss == ee) { return; }
    int m = (ss + ee) >> 1;
    build(i + i, ss, m); build(i + i + 1, m + 1, ee);
  }
  void debug(int i = 1) {
    auto nn = make_pair(make_pair(st[i], en[i]), t[i]);
    error(nn);
    if (st[i] == en[i]) { return; }
    debug(i + i); debug(i + i + 1);
  }
  inline void push(int i) {
    i64 &lza = t[i].lza, &lzd = t[i].lzd;
    if (lza == 0 && lzd == 0) { return; }
    i64 len = en[i] - st[i] + 1;
    t[i].sum += len * lza + lzd * (len * (len - 1) / 2);
    if (len > 1) {
      t[i + i].lza += lza;
      t[i + i].lzd += lzd;
      t[i + i + 1].lza += lza + lzd * (en[i + i] - st[i + i] + 1);
      t[i + i + 1].lzd += lzd;
    }
    lza = lzd = 0;
  }
  inline void update(int i, int us, int ue, i64 a) {
    if (us <= st[i] && en[i] <= ue) {
      t[i].lza += a;
      t[i].lzd++;
      push(i); return;
    }
    push(i);
    if (ue < st[i] || en[i] < us) { return; }
    i64 b = a + (en[i + i] - max(us, st[i]) + 1);
    if (us > en[i + i]) b = a;
    update(i + i, us, ue, a); update(i + i + 1, us, ue, b);
    t[i] = t[i + i] + t[i + i + 1];
  }
  inline Node ask(int i, int qs, int qe) {
    push(i);
    if (qs == st[i] && qe == en[i]) { return t[i]; }
    if (qs > en[i + i]) { return ask(i + i + 1, qs, qe); }
    if (qe < st[i + i + 1]) { return ask(i + i, qs, qe); }
    return ask(i + i, qs, en[i + i]) +
      ask(i + i + 1, st[i + i + 1], qe);
  }
  void update(int L, int R) {
    return update(1, L, R, 1);
  }
  i64 ask(int L, int R) {
    return ask(1, L, R).sum;
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  cin >> n >> q;
  SegTree seg(n);
  while (q--) {
    int type, L, R;
    cin >> type >> L >> R;
    if (type == 0) {
      seg.update(L, R);
    } else {
      cout << seg.ask(L, R) << endl;
    }
    //~ seg.debug();
  }
    
  return 0;
}
