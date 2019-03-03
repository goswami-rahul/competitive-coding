/*
 * First, sort the items according first element. Then iterate
 * over the items in this order, considering ith items first element
 * to be the largest first item of the selected set.
 * Now, for each such ith item's turn, sort the items upto ith item,
 * this time considering second element and iterate over this order.
 * Also maintain a set of smallest k items considering third element
 * and update the answer for each iteration.
 * Total Time Complexity - O(n ^ 2 log n) 
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

  int n, k;
  cin >> n >> k;
  vector<vector<int>> a(n, vector<int>(3));
  for (auto &x: a) for (auto &e: x) cin >> e;
  sort(ALL(a));
  i64 ans = INF;
  for (int i = k - 1; i < n; ++i) {
    vector<vector<int>> b(i + 1, vector<int>(2));
    for (int j = 0; j <= i; ++j) {
      b[j][0] = a[j][1];
      b[j][1] = a[j][2];
    }
    sort(ALL(b));
    multiset<int> s;
    for (int j = 0; j <= i; ++j) {
      s.insert(b[j][1]);
      if (SZ(s) > k) s.erase(prev(s.end()));
      if (SZ(s) < k) continue;
      uin(ans, (i64) a[i][0] + b[j][0] + (*s.rbegin()));
    }
  }
  cout << ans << '\n';
    
  return 0;
}
