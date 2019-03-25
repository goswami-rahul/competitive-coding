/*
 * We select the parcel to be dropped in decreasing order of their
 * destination's distance from the source.
 * Then, we simulate the process, for each starting points in
 * O(n * m)
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
#define dis(from, to) ((to > from) ? to - from : n + to - from)

static vector<int> b[5000];
static int to[5000], fo[5000];
int main()
{

  int n, m;
  scanf(" %d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int x, y;
    //~ cin >> x >> y;
    scanf(" %d %d", &x, &y);
    --x; --y;
    if (b[x].empty()) b[x].push_back(0);
    b[x].push_back(y);
    ++b[x][0];
  }
  for (int i = 0; i < n; ++i) if (!b[i].empty()) {
    sort(b[i].begin() + 1, b[i].end(), [&] (int x, int y) {
      return dis(i, x) < dis(i, y);
    });
  }
  for (int i = 0; i < n; ++i) {
    iota(to, to + n, 1); to[n - 1] = 0;
    iota(fo, fo + n, -1); fo[0] = n - 1;
    int rem = m, ans = 0, d = 0, cur = i;
    while (true) {
      if (b[cur].empty() || b[cur][0] == 0) {
        to[fo[cur]] = to[cur];
        fo[to[cur]] = fo[cur];
      } else {
        rem--;
        uax(d, dis(cur, b[cur][b[cur][0]]));
        --b[cur][0];
        if (rem == 0) {
          ans += d;
          printf("%d ", ans);
          break;
        }
      }
      d -= dis(cur, to[cur]);
      ans += dis(cur, to[cur]);
      cur = to[cur];
    }
    for (int j = 0; j < n; ++j) if (!b[j].empty()) {
      b[j][0] = SZ(b[j]) - 1;
    }
  }
  
  return 0;
}
