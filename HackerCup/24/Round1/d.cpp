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

const i64 INF = (i64) 1e12 + 42;

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


void SolveCase() {
  string s; int k; cin >> s >> k; --k;
  int n = s.size();
  for (int i = n - 1; i > 0; --i) {
    if (s[i] != '?' && s[i] > '6' && s[i - 1] == '?') {
      s[i - 1] = '1';
    }
  }
  vector<int> opt;
  vector<string> ops;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '?' && i < n - 1) opt.push_back(2), ops.push_back("21");
    else opt.push_back(1), ops.push_back(string{s[i]});
  }

  if (s[n-1] == '?') {
    if (s[n-2] == '2') {
      opt.push_back(7);
      ops.push_back("6543210");
    } else {
      opt.push_back(10);
      ops.push_back("9876543210");
    }
  }
  vector<i64> ms(n+1, 1);
  for (int i = n - 1; i >= 0; --i) {
    ms[i] = opt[i] * ms[i+1];
    uin(ms[i], INF);
  }
  string ans;
  for (int i = 0; i < n; ++i) {
    ans += ops[i][0];
    for (int j = 1; j < ops[i].size(); ++j) {
      if (k >= ms[i+1]) {
        k -= ms[i+1];
        ans.back() = ops[i][j];
      } else {
        break;
      } 
    }
  }

  vector<int> dpj(n + 1), dpi(n + 1);
  dpi[0] = 1;
  for (int i = 1; i <= n; ++i) {
    if (ans[i-1] != '0') dpi[i] = add(dpi[i-1], dpj[i-1]);
    if (i < 2) continue;
    if (ans[i-2] == '1') adds(dpj[i], dpi[i-1]);
    if (ans[i-2] == '2' && ans[i-1] <= '6') adds(dpj[i], dpi[i-1]);
  }
  cout << ans << ' ' << add(dpi[n], dpj[n]) << '\n';

}

int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": "; SolveCase();   
  }
}
