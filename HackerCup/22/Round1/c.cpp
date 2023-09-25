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
const i64 INF = (i64) 8e18 + 42;

// Convex hull from https://cp-algorithms.com/geometry/convex-hull.html#grahams-scan-algorithm
struct pt {
    i64 x, y;
};

string to_string(pt p) {
  return to_string(pair{p.x, p.y});
}

int orientation(pt a, pt b, pt c) {
    i64 v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<pt>& a, bool include_collinear = false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    a = st;
}

i64 Dis(pt one, pt two) {
  return (one.x - two.x) * (one.x - two.x) + (one.y - two.y) * (one.y - two.y);
}

i64 Calc(vector<pt> a, i64 k, i64 d) {
  error(a)
  int n = a.size();
  i64 ans = 0;
  int i = 0;
  while (i < n - 1) {
    int j = i + 1;
    while (j < n) {
      i64 e = Dis(a[i], a[j]);
      if (e > d * d) break;
      ++j;
      if (e > k) break;
    }
    --j;
    if (i == j) return INF;
    i64 cur = max(k, Dis(a[i], a[j]));
    uin(cur, k + max(k, Dis(a[j-1], a[j])));
    ans += cur;
    i = j;
  }
  error(ans)
  return ans;
}

i64 SolveCase() {
  int n, k, d; cin >> n >> k >> d;
  vector<pt> a(n);
  for (auto &p : a) cin >> p.x >> p.y;
  convex_hull(a);
  n = a.size();
  int beg = min_element(ALL(a), Luv(u.x < v.x)) - a.begin();
  int fin = max_element(ALL(a), Luv(u.x < v.x)) - a.begin();
  error(n, beg, fin)
  error(a)
  vector<pt> l, r;
  for (int i = beg;; i = (i + 1) % n) {
    l.push_back(a[i]);
    if (i == fin) break;
  }
  for (int i = beg;; i = (i + n - 1) % n) {
    r.push_back(a[i]);
    if (i == fin) break;
  }
  error(l, r)
  i64 ans = min(Calc(l, k, d), Calc(r, k, d));
  if (ans == INF) ans = -1;
  error(ans)
  return ans;
}

int main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int tt; cin >> tt;
  for (int t = 1; t <= tt; ++t) {
    error(t)
    cout << "Case #" << t << ": " << SolveCase() << '\n';
  }
} 