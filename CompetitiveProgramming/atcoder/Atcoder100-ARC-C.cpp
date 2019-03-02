/*
 * Maintain a set for each mask m, such that it contains largest two
 * numbers of all numbers with indices as submask of m.
 * Then print answer as prefix maximums of the sum of set elements.
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
using i64 = unsigned long long int;
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

  int n;
  cin >> n;
  vector<int> a(1 << n);
  for (int &e: a) cin >> e;
  vector<set<pair<int,int>>> s(1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    s[i].emplace(a[i], i);
  }
  for (int i = 0; i < (1 << n); ++i) {
    for (int k = 0; k < n; ++k) {
      if (i >> k & 1) {
        for (const auto &e: s[i - (1 << k)]) {
          s[i].insert(e);
          if (SZ(s[i]) > 2) s[i].erase(s[i].begin());
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i < (1 << n); ++i) {
    int sum = 0;
    assert(SZ(s[i]) == 2);
    for (const auto &e: s[i]) sum += e.first;
    uax(ans, sum);
    cout << ans << '\n';
  }
  
  return 0;
}
