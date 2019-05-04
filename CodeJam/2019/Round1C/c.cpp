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
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/
vector<string> a;
int r, c;
const int H = 0, V = 1;

bool win(int x, int y, int dir) {
  if (x < 0 || x >= r || y < 0 || y >= c) return false;
  if (a[x][y] != '.') return false;
  string old;
  if (dir == H) {
    old = a[x];
    bool ok = true;
    for (int i = y; i < c && ok; ++i) {
      if (a[x][i] == '$') break;
      if (a[x][i] == '#') ok = false;
      a[x][i] = '$';
    }
    for (int i = y - 1; i >= 0 && ok; --i) {
      if (a[x][i] == '$') break;
      if (a[x][i] == '#') ok = false;
      a[x][i] = '$';
    }
    for (int i = 0; i < r && ok; ++i) {
      for (int j = 0; j < c && ok; ++j) {
        if (win(i, j, H) || win(i, j, V)) ok = false;
      }
    }
    a[x] = old;
    return ok;
  }
  if (dir == V) {
    for (int i = 0; i < r; ++i) {
      old += a[i][y];
    }
    bool ok = true;
    for (int i = x; i < r && ok; ++i) {
      if (a[i][y] == '$') break;
      if (a[i][y] == '#') ok = false;
      a[i][y] = '$';
    }
    for (int i = x - 1; i >= 0 && ok; --i) {
      if (a[i][y] == '$') break;
      if (a[i][y] == '#') ok = false;
      a[i][y] = '$';
    }
    for (int i = 0; i < r && ok; ++i) {
      for (int j = 0; j < c && ok; ++j) {
        if (win(i, j, H) || win(i, j, V)) ok = false;
      }
    }
    for (int i = 0; i < r; ++i) a[i][y] = old[i];
    return ok;
  }
}

void test_case() {
  
  cin >> r >> c;
  a.resize(r);
  int ans = 0;
  for (auto &s: a) cin >> s;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      ans += win(i, j, H);
      ans += win(i, j, V);
    }
  }
  cout << ans << '\n';
  
  return;
}

signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": ";
    test_case();
  }
  
  return 0;
}
