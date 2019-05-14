/*
 * Maintain a set "pos" which contains the indices of the required
 * "special" flowers such that the minimum index in the set is as
 * rightmost as possible. To maintain it, keep a collection of sets
 * which rightmost "f" indices of a flower, where "f" is its frequency
 * in b.
 * Now, at each position, find the total collections formed, if it is >= n
 * construct the answer.
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
inline ostream &operator << (ostream & os, set<T>& v) {
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

signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, k, n, s;
  const int nax = 500000 + 42;
  cin >> m >> k >> n >> s;
  vector<int> a(m), b(s), req(nax, 0);
  for (auto &z: a) cin >> z;
  for (auto &z: b) cin >> z, req[z]++;
  
  set<int> pos;
  vector<set<int>> sets(nax);
  for (int i = 0; i < m; ++i) {
    int x = a[i];
    if (req[x] == 0) continue;
    pos.insert(i);
    sets[x].insert(i);
    if (req[x] < SZ(sets[x])) {
      pos.erase(*sets[x].begin());
      sets[x].erase(sets[x].begin());
    }
    if (SZ(pos) < s) continue;
    assert (SZ(pos) == s);
    int left = *pos.begin();
    int now = *prev(pos.end());
    assert (now == i);
    int cnt = left / k;
    int rem = k - (now - left + 1 + left % k);
    uax(rem, 0);
    if (now + rem < m) {
      ++cnt;
      cnt += (m - 1 - now - rem) / k;
    }
    if (cnt >= n) {
      vector<int> ans;
      for (int j = left + 1; j < now; ++j) {
        if (!pos.count(j)) ans.push_back(j + 1);
      }
      int sz = now - left + 1;
      if (sz >= k) {
        for (int j = s; j < k; ++j)
          ans.pop_back();
        for (int j = 0; j < left % k; ++j)
          ans.push_back(j + 1);
      } else {
        ans.clear();
        for (int j = 0; j < left % k - (k - sz); ++j)
          ans.push_back(j + 1);
      }
      cout << SZ(ans) << '\n';
      for (int z: ans) cout << z << ' ';
      return 0;
    }
  }
  cout << "-1\n";
  return 0;
}
