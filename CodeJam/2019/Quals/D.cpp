#include <bits/stdc++.h>
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
using namespace std;

vector<int> ask(const vector<int> &a, int offset) {
  for (int i = 0; i < SZ(a) - offset; ++i) {
    cout << a[i];
  }
  cout << endl;
  string s; cin >> s;
  if (s == "-1") exit(0);
  vector<int> b;
  for (char c: s) {
    b.push_back(c == '1');
  }
  for (int i = SZ(a) - offset; i < SZ(a); ++i) {
    b.push_back(a[i]);
  }
  return b;
}
void show(const vector<int> &ans) {
  for (int x: ans) {
    cout << x << ' ';
  }
  cout << endl;
  int r;
  cin >> r;
  if (r == -1) exit(0);
}

void test_case() {
  int n, b, f;
  cin >> n >> b >> f;
  int lg = 0, offset;
  for (int p = 1;;) {
    if (p >= n) {
      offset = p - n;
      n = p;
      break;
    }
    p <<= 1;
    ++lg;
  }
  vector<vector<int>> rs;
  for (int p = 2; p <= n && p <= 32; p <<= 1) {
    vector<int> q(p, 0);
    fill(q.begin() + (p >> 1), q.end(), 1);
    while (SZ(q) < n) {
      vector<int> t(q);
      q.insert(q.end(), ALL(t));
    }
    vector<int> r = ask(q, offset);
    assert(SZ(r) + b == n);
    rs.push_back(r);
  }
  //~ [x, y)
  vector<int> ans;
  function<void(int,int,int,int)>
  recur = [&] (int lv, int x, int y, int s) {
    if (0 == lv) {
      if (y == x) ans.push_back(s);
      return;
    }
    --lv;
    int p = x;
    for (; p < y; ++p) {
      if (rs[lv][p]) break;
    }
    recur(lv, x, p, s); recur(lv, p, y, s + (1 << lv));
  };
  if (n <= 16) {
    recur(lg, 0, n - b, 0);
  } else {
    for (int p = 0, x = 0, y; p < n; p += 16) {
      y = x;
      while (y < n - b && rs[4][y] == rs[4][x])
        ++y;
      recur(4, x, y, p);
      x = y;
    }
  }
  show(ans);
}

signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt;
  cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    test_case();
  }
  
  return 0;
}
