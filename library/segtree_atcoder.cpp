#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// https://atcoder.jp/contests/abc415/tasks/abc415_f
// run 
// $ ./ac-library/expander.py --console F_Max_Combo.cpp > new_file.cpp
struct info {
  char lc;
  char rc;
  int ans;
  int pre;
  int suf;
  bool eq;
};

info op(info a, info b) {
  return info{
    .lc = a.lc,
    .rc = b.rc,
    .ans = max({a.ans, b.ans, (a.rc == b.lc ? a.suf + b.pre : 0)}),
    .pre = a.eq && a.lc == b.lc ? a.pre + b.pre : a.pre,
    .suf = b.eq && b.rc == a.rc ? b.suf + a.suf : b.suf,
    .eq = a.eq && b.eq && a.lc == b.lc
  };
}

info create(char c) {
  return info{c, c, 1, 1, 1, true};
}

info e() {
  return info{'_', '_', 0, 0, 0, 0};
}


int32_t main() {
  cin.tie(nullptr) -> sync_with_stdio(false);
  int n, q; cin >> n >> q;
  atcoder::segtree<info, op, e> seg(n);
  for (int i = 0; i < n; ++i) {
    char c; cin >> c;
    seg.set(i, create(c));
  }
  while (q--) {
    int t, l; cin >> t >> l; --l;
    if (t == 1) {
      char c; cin >> c;
      seg.set(l, create(c));
    } else {
      int r; cin >> r;
      cout << seg.prod(l, r).ans << '\n';
    }
  }
}