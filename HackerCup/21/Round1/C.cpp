#ifdef Rahul
#include "RAHUL.h"
#else
#include <bits/stdc++.h>
using namespace std;
#define error(...) 42;
#endif
#define SZ(v) int((v).size())
#define ALL(vec) begin(vec), end(vec)
using i64 = int64_t;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
#define Luv(...) [&] (auto &&u, auto &&v) { return __VA_ARGS__; }
const int MOD = (int) 1e9 + 7;
const i64 INF = (i64) 1e18 + 42;

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

struct UF {
  vector<int> par, sz;
  UF(int n): par(n), sz(n, 1) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int u) {
    return (u == par[u] ? u : par[u] = find(par[u]));
  }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    par[v] = u;
    sz[u] += sz[v];
    return true;
  }
  int size(int u) {
    return sz[find(u)];
  }
};


const int K = 22;
using state = array<int, K>;
const int N = 8e5 + 42;
vector<pair<int,int>> g[N];
state a[N];
int sum;

inline void Merge(state &x, const state &y, int c) {
  for (int i = 0; i < K; ++i) {
    x[min(i, c)] += y[i];
  }
}

inline void Remove(state &x, const state &y, int c) {
  for (int i = 0; i < K; ++i) {
    x[min(i, c)] -= y[i];
  }
}

// inline int Calc(const state &x, const state &y, int c) {
inline int Calc(state x, state y, int c) {
  int res = 0, xs = 0, ys = 0;
  for (int i = K - 1; i > 0; --i) {
    if (i > c) {
      x[i - 1] += x[i];
      y[i - 1] += y[i];
    }
    if (i <= c) {
      int cur = 0;
      adds(cur, mul(xs, y[i]));
      adds(cur, mul(ys, x[i]));
      adds(cur, mul(x[i], y[i]));
      adds(res, mul(i, cur));
      xs += x[i], ys += y[i];
    }
  }
  return res;
}

void Root(int u = 0, int p = -1) {
  fill(ALL(a[u]), 0);
  a[u][21] = 1;
  for (auto [v, c] : g[u]) {
    if (v != p) {
      Root(v, u), Merge(a[u], a[v], c);
    }
  }
}

int Solve(int u = 0, int p = -1) {
  int ans = 1;
  for (auto [v, c] : g[u]) {
    if (v != p) {
      Remove(a[u], a[v], c);
      muls(ans, sub(sum, Calc(a[u], a[v], c)));
      // b.push_back(Calc(a[u], a[v], c));
      Merge(a[v], a[u], c);
      muls(ans, Solve(v, u));
      Remove(a[v], a[u], c);
      Merge(a[u], a[v], c);
    }
  }
  return ans;
}

int SolveCase() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) g[i].clear();
  vector<array<int, 3>> edges;
  for (int i = 0; i < n - 1; ++i) {
    int u, v, c; cin >> u >> v >> c, --u, --v;
    g[u].emplace_back(v, c);
    g[v].emplace_back(u, c);
    edges.push_back({c, u, v});
  }
  sort(ALL(edges), greater{});
  UF uf(n);
  sum = 0;
  for (auto [c, u, v] : edges) {
    adds(sum, mul(c, mul(uf.size(u), uf.size(v))));
    uf.join(u, v);
  }
  Root();
  return Solve();
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 