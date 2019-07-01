#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
#define PB push_back
#define MP make_pair
#define LL long long
#define int LL
#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define RE(i,n) FOR(i,1,n)
#define REP(i,n) FOR(i,0,(int)(n)-1)
#define R(i,n) REP(i,n)
#define VI vector<int>
#define PII pair<int,int>
#define LD long double
#define FI first
#define SE second
#define st FI
#define nd SE
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

#define unordered_map __fast_unordered_map
template<class Key, class Value, class Hash = std::hash<Key>>
using unordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;

template<class C> void mini(C &a4, C b4) { a4 = min(a4, b4); }
template<class C> void maxi(C &a4, C b4) { a4 = max(a4, b4); }

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
}

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

// some code copied from EBAIT from snackdown 2019 elimination round
struct Fraction {
  int p, q;
  bool operator<(const Fraction& other) const {
    return p * other.q < q * other.p;
  }

  vector<int> GetCC() const {
    int s = p / q;
    Fraction f{q, p - s * q};
    if (f.q == 0) { return {s}; }
    vector<int> other_cc = f.GetCC();
    other_cc.insert(other_cc.begin(), s);
    return other_cc;
  }

  static Fraction FromCC(VI cc) {
    reverse(ALL(cc));
    Fraction f{0, 1};

    bool is_first = true;
    for (int x : cc) {
      if (is_first) {
        is_first = false;
      } else {
        f = Fraction{f.q, f.p};
      }

      f.p += f.q * x;
    }

    assert(f.p <= 2e18 && f.q <= 2e18);
    return f;
  }
};

Fraction Approximate(Fraction lbound, Fraction rbound) {
  vector<int> lbound_cc = lbound.GetCC();
  vector<int> rbound_cc = rbound.GetCC();
  assert(count(lbound_cc.begin() + 1, lbound_cc.end(), 0) == 0);
  assert(count(rbound_cc.begin() + 1, rbound_cc.end(), 0) == 0);
  debug(lbound.p, lbound.q, lbound_cc);
  debug(rbound.p, rbound.q, rbound_cc);

  for (auto add_l : {false, true}) {
    for (auto add_r : {false, true}) {
      vector<int> lcc = lbound_cc;
      vector<int> rcc = rbound_cc;
      if (add_l) { --lcc.back(); lcc.PB(1); }
      if (add_r) { --rcc.back(); rcc.PB(1); }
      vector<int> res_cc;
      int ptr = 0;
      while (ptr < SZ(lcc) && ptr < SZ(rcc) && lcc[ptr] == rcc[ptr]) {
        res_cc.PB(lcc[ptr]);
        ++ptr;
      }
      int min_val = 2e9;
      if (ptr < SZ(lcc)) { mini(min_val, lcc[ptr]); }
      if (ptr < SZ(rcc)) { mini(min_val, rcc[ptr]); }
      assert(min_val < 1.5e9);

      res_cc.PB(min_val + 1);
      auto best_frac = Fraction::FromCC(res_cc);
      debug(lcc, rcc, res_cc, best_frac.p, best_frac.q);

      if (lbound < best_frac && best_frac < rbound) {
        return best_frac;
      }
    }
  }
  assert(false);
}

struct Testcase {
  int test_idx_;
  Testcase(int tidx) : test_idx_(tidx) {}

  VI Solve() {
    int N;
    cin >> N;
    vector<PII> elems(N);
    for (auto &el : elems) { cin >> el.st >> el.nd; }

    Fraction lbound{0, 1};
    Fraction ubound{(int)2e9, 1};

    for (int i = 1; i < N; ++i) {
      const int c1 = elems[i - 1].st;
      const int j1 = elems[i - 1].nd;
      const int c2 = elems[i].st;
      const int j2 = elems[i].nd;

      if (c1 >= c2 && j1 >= j2) { return {}; }
      if (c1 <= c2 && j1 <= j2) { continue; }

      if (c1 < c2) {
        assert(j1 - j2 > 0);
        maxi(lbound, Fraction{j1 - j2, c2 - c1});
      } else {
        assert(j2 - j1 > 0);
        mini(ubound, Fraction{j2 - j1, c1 - c2});
      }
    }

    debug(lbound.p, lbound.q, ubound.p, ubound.q);
    if (!(lbound < ubound)) { return {}; }
    auto ans = Approximate(lbound, ubound);
    return {ans.p, ans.q};
  }

  void Run() {
    auto ans = Solve();

    cout << "Case #" << test_idx_ << ": ";
    if (ans.empty()) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << ans[0] << " " << ans[1] << "\n";
    }
  }
};


int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(11);
  cerr << fixed << setprecision(6);

  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    Testcase(i).Run();
  }
}

