#ifdef Rahul
# include "RAHUL.h"
#else
# include <bits/stdc++.h>
  using namespace std;
# define error(...) 42;
#endif
#define SZ(v) int((v).size())
#define ALL(vec) begin(vec), end(vec)
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
#define Luv(...) [&] (auto &&u, auto &&v) { return __VA_ARGS__; }
using i64 = int64_t;
const i64 INF = (i64) 1e18 + 42;

const int MOD = 998244353;
inline int add(int a, int b, int mod = MOD) {
  a += b; return a >= mod ? a - mod : a;
}
inline int sub(int a, int b, int mod = MOD) {
  a -= b; return a < 0 ? a + mod : a;
}
inline int mul(int a, int b, int mod = MOD) {
  return int((long long) a * b % mod);
}
inline int mpow(int base, long long ex, int mod = MOD) {
  int res = 1;
  for (; ex > 0; ex >>= 1) {
    if (ex & 1) res = mul(res, base, mod);
    base = mul(base, base, mod);
  }
  return res;
}
inline int inv(int a, int mod = MOD) {
  return mpow(a, mod - 2, mod);
}
inline int mdiv(int a, int b, int mod = MOD) {
  return mul(a, mpow(b, mod - 2,  mod));
}
inline void adds(int &a, int b, int mod = MOD) {
  a += b; if (a >= mod) a -= mod;
}
inline void subs(int &a, int b, int mod = MOD) {
  a -= b; if (a < 0) a += mod;
}
inline void muls(int &a, int b, int mod = MOD) {
  a = int((long long) a * b % mod);
}
inline void mdivs(int &a, int b, int mod = MOD) {
  a = mdiv(a, b, mod);
}

struct Node {
  string s;
  array<int, 26> ch;
};
const int M = 1e5;
Node t[M];
int ctr = 3;

void add(string s, int root) {
  for (int i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (c == '?') {
      t[root].s = s.substr(i);
      break;
    }
    int &ch = t[root].ch[c - 'A'];
    if (ch == 0) {
      if (!t[root].s.empty()) {
        
      }
      ch = ctr++;
    }
    root = ch;
  }
}

int SolveCase() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;

  }
}

int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';   
  }
}
