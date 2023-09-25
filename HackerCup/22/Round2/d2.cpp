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
#define int i64

int Calc(array<int, 4> a, array<int, 4> b) {
  int sa = a[1] + a[2] * 2 + a[3] * 3;
  int sb = b[1] + b[2] * 2 + b[3] * 3;
  if (sa > sb) swap(a, b), swap(sa, sb);
  int d = sb - sa;
  if (d % 2) return -1;
  d /= 2;
  int m = min({a[1], b[3], d / 2});
  int ans = m;
  d -= m * 2;
  a[1] -= m, a[3] += m;
  b[3] -= m, b[1] += m;
  m = min({a[1], b[2], d});
  ans += m;
  d -= m;
  a[1] -= m, a[2] += m;
  b[2] -= m, b[1] += m;
  m = min({a[2], b[3], d});
  ans += m;
  d -= m;
  if (d > 0) return -1;
  return ans;
}

const int LOGN = 26;
template <class T>
struct Fenwick {
  int n;
  vector<T> bit;
  Fenwick(int _n): n(_n), bit(n + 1, 0) {};
  Fenwick(int _n, int inival): n(_n), bit(n + 1, 0) {
    for (int i = 1; i <= n; ++i)
      add(i, inival);
  }
  T ask(int R) {
    T ans = 0;
    for(int x = R; x > 0; x -= x & -x)
      ans += bit[x];
    return ans;
  }
  T ask(int L, int R) {
    return ask(R) - ask(L - 1);
  }
  T at(int pos) {
    return ask(pos, pos);
  }
  void add(int pos, T v) {
    if(pos <= 0) return;
    for(; pos <= n; pos += pos & -pos)
        bit[pos] += v;
  }
  // greatest idx with cumulative sum = k
  int kth(int k) {
    int idx = 0;
    for (int mask = 1 << LOGN; mask; mask >>= 1) {
      int cur = idx + mask;
      if (cur <= n && bit[cur] <= k) {
        k -= bit[cur];
        idx = cur;
      }
    }
    return (k == 0 ? idx : -1);
  };
  vector<T> values(int upto = -1) {
    if (upto == -1) return values(n);
    vector<T> fenwick_values;
    for (int i = 1; i <= upto; ++i)
        fenwick_values.push_back(ask(i, i));
    return fenwick_values;
  }
};

i64 SolveCase() {
  i64 total = 0;
  int n, m; cin >> n >> m;
  vector<int> a(n + 1);
  Fenwick<i64> onef(n + 1), twof(n + 1);
  Fenwick<i64> onep(n + 1), twop(n + 1);
  int ones = 0, twos = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i] == 1) onef.add(i, 1), onep.add(i, i), ones++;
    if (a[i] == 2) twof.add(i, 1), twop.add(i, i), twos++;
  }
  while (m--) {
    int i, v, p; cin >> i >> v >> p;
    if (a[i] == 1) onef.add(i, -1), onep.add(i, -i), ones--;
    if (a[i] == 2) twof.add(i, -1), twop.add(i, -i), twos--;
    a[i] = v;
    if (a[i] == 1) onef.add(i, 1), onep.add(i, i), ones++;
    if (a[i] == 2) twof.add(i, 1), twop.add(i, i), twos++;
    int ls = onef.ask(p) + 2 * twof.ask(p);
    int rs = ones + 2 * twos - ls;
    if (abs(ls - rs) % 2) {
      total--;
      continue;
    }
    if (ls == rs) continue;
    int ans = 0;
    if (ls < rs) {
      int d = (rs - ls) / 2;
      if (onef.ask(p) < d || twof.ask(p + 1, n) < d) {
        total--;
        continue;
      }
      int t = onef.kth(onef.ask(p) - d) + 1;
      ans += d * d;
      ans += p * d - d * (d - 1) / 2 - onep.ask(t, p);
      t = twof.kth(twof.ask(p) + d - 1) + 1;
      ans += twop.ask(p + 1, t);
      ans -= p * d + d * (d + 1) / 2; 
    } else {
      int d = (ls - rs) / 2;
      swap(twof, onef);
      swap(twop, onep);
      if (onef.ask(p) < d || twof.ask(p + 1, n) < d) {
        total--;
        swap(twof, onef);
        swap(twop, onep);
        continue;
      }
      int t = onef.kth(onef.ask(p) - d) + 1;
      ans += d * d;
      ans += p * d - d * (d - 1) / 2 - onep.ask(t, p);
      t = twof.kth(twof.ask(p) + d - 1) + 1;
      ans += twop.ask(p + 1, t);
      ans -= p * d + d * (d + 1) / 2; 
      swap(twof, onef);
      swap(twop, onep);
    }
    total += ans;
  }
  return total;
}

int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 