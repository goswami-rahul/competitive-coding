/*
 * Maintain three deques for the segments
 * [1, L-1], [L, R], [R+1, n]
 * keep a boolean "rev" which tells if the current
 * segment is reversed or not.
 * to move heads, shift one element from one que to
 * another adjacent queue.
 * 
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

signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, L, R;
  cin >> n >> L >> R;
  --L; --R;
  string s;
  cin >> s;
  deque<char> lq, mq, rq;
  for (int i = 0; i < n; ++i) {
    if (i < L) lq.push_back(s[i]);
    else if (i <= R) mq.push_back(s[i]);
    else rq.push_back(s[i]);
  }
  bool rev = false;
  int qq; cin >> qq;
  while (qq--) {
    char c;
    cin >> c;
    if (c == 'Q') {
      char which;
      cin >> which;
      int is_lf = (which == 'L') ^ rev;
      cout << (is_lf ? mq.front() : mq.back());
    } else if (c == 'R') {
      rev ^= 1;
    } else if (c == 'S') {
      char which, dir;
      cin >> which >> dir;
      if (which == 'L') {
        if (which == dir) {
          char ch = lq.back();
          lq.pop_back();
          rev ? mq.push_back(ch) : mq.push_front(ch);
        } else {
          char ch = rev ? mq.back() : mq.front();
          rev ? mq.pop_back() : mq.pop_front();
          lq.push_back(ch);
        }
      } else {
        if (which == dir) {
          char ch = rq.front();
          rq.pop_front();
          rev ? mq.push_front(ch) : mq.push_back(ch);
        } else {
          char ch = rev ? mq.front() : mq.back();
          rev ? mq.pop_front() : mq.pop_back();
          rq.push_front(ch);
        }
      }
    }
  }
  cout << '\n';
  
  return 0;
}
