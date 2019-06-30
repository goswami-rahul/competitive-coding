/**
 * We will calculate Grundy of the game to determine the winner.
 * Since it is independent for each prime, grundy of game = xor of grundy of each prime
 * for each prime, count how many times it appears in each number, and
 * represent the state as a bitmask with ith bit set if the prime appears i times
 * in some number.
 * We find the transitions for every amount we take, and calculate grundy recursively
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef long long i64;
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
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
int32_t main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  const int nax = 1e5;
  vector<int> primes, a(n);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    a[i] = x;
    for (int j = 2; j < nax; ++j) {
      int cnt = 0;
      while (x % j == 0) {
        x /= j;
        cnt++;
      }
      if (cnt) primes.push_back(j); 
    }
    if (x > 1) primes.push_back(x);
  }
  sort(ALL(primes));
  primes.erase(unique(ALL(primes)), primes.end());
  int m = SZ(primes);
  vector<vector<int>> stones(m, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    int x = a[i];
    for (int j = 0; j < m; ++j) {
      while (x % primes[j] == 0) {
        x /= primes[j];
        stones[j][i]++;
      }
    }
    assert (x == 1);
  }
  int ans = 0;
  map<i64,int> seen;
  for (auto &s: stones) {
    sort(ALL(s));
    reverse(ALL(s));
    s.erase(unique(ALL(s)), s.end());
    if (s.back() == 0) s.pop_back();
    i64 start = 0;
    for (int x: s) start |= 1LL << x;
    function<int(i64)> grundy = [&] (i64 state) {
      if (auto it = seen.find(state); it != seen.end()) return it->second;
      i64 has = 0;
      for (int take = 1;; ++take) {
        i64 new_state = state >> take;
        new_state |= state & ((1LL << take) - 1);
        if (new_state & 1) new_state ^= 1;
        if (new_state == state) break;
        has |= 1LL << grundy(new_state);
      }
      for (int bit = 0;; ++bit) 
        if (!(has >> bit & 1)) return seen[state] = bit;
    };
    ans ^= grundy(start);
  }
  cout << (ans ? "Mojtaba" : "Arpa") << '\n';
  
  return 0;
}
