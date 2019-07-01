#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
 
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string>) {}
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2> buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (const auto e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1000000007;
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//~ mt19937_64 rng(42);
inline i64 randint(i64 a, i64 b) {
  return uniform_int_distribution<i64>(a, b)(rng);
}
i64 ask() {
  i64 p; cin >> p;
  if (p == -1) exit(0);
  return p;
}

void say(i64 p) {
  cout << p << endl;
}
const i64 diff = 10000000000LL, LIM = 1000000000000LL;
set<pair<i64,i64>> s;
void remove(i64 p) {
  auto it = s.upper_bound(make_pair(p, p + diff));
  assert (it != s.begin()); --it;
  assert (it->second >= p + diff);
  i64 st = it->first, en = it->second;
  s.erase(it);
  if (p - st >= diff) s.emplace(st, p);
  if (en - p - diff >= diff) s.emplace(p + diff, en);
}
void test_case() {
  s = set<pair<i64,i64>>{make_pair(1LL, LIM + 1)};
  while (true) {
    i64 his;
    his = ask();
    if (his < 0LL) return;
    remove(his);
    //~ auto it = s.lower_bound(make_pair(randint(1, LIM), LIM));
    auto it = s.begin();
    if (it == s.end()) --it;
    i64 st = it->first, en = it->second;
    i64 my = randint(st, en - diff);
    say(my);
    remove(my);
  }
}

int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt, w;
  cin >> tt >> w;
  for (int t = 1; t <= tt; ++t) {
    test_case();
  }
  
  return 0;
}
