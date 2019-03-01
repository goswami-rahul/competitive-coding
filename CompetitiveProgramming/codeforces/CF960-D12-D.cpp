/*
 * maintain an array of size 64, denoting the shift at ith level
 * for query 1, simply add k to arr[level(i)]
 * for query 2, shift current node by k, next by 2*k, 4*k, 8*k, ...
 * for query 3, shift back the nodes, and print the answers.
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

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int q;
  cin >> q;
  vector<i64> a(64, 0LL);
  while (q--) {
    int type;
    cin >> type;
    i64 x; cin >> x;
    int d = __lg(x);
    if (type == 1) {
      i64 k; cin >> k;
      a[d] = (a[d] + k) % (1LL << d);
    } else if (type == 2) {
      i64 k; cin >> k;
      k %= (1LL << d);
      if (k < 0) k += (1LL << d);
      for (int i = d; i < 63; ++i) {
        a[i] = (a[i] + k) % (1LL << i);
        k = (k << 1) % (1LL << (i + 1));
      }
    } else {
      x -= (1LL << d);
      for (int i = d; ; --i) {
        cout << (1LL << i) + x << ' ';
        if (i == 0) break;
        x = (x + a[i]) % (1LL << i);
        x >>= 1;
        x = (x - a[i - 1]) % (1LL << (i - 1));
        if (x < 0) x += (1LL << (i - 1));
      }
      cout << '\n';
    }
  }
    
  return 0;
}
