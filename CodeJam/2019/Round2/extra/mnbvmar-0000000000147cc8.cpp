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

const int N = 100;
const int kVases = 20;
const int kWinners = 5;
const int kCooldown = 9;

struct Testcase {
  int test_idx_;
  Testcase(int tidx) : test_idx_(tidx) {}
  int meh;

  void Run() {
    int num_ops = 0;
    for (int i = 0; i < N - kCooldown - kWinners; ++i) {
      ++num_ops;
      cin >> meh;
      cout << i % (kVases - kWinners) + 1 << " " << 1 << endl;
    }

    for (int i = 0; i < kWinners; ++i) {
      ++num_ops;
      cin >> meh;
      cout << kVases - i << " " << N << endl;
    }

    vector<int> sizes(kWinners);
    for (int i = 0; i < kWinners; ++i) {
      ++num_ops;
      cin >> meh;
      cout << kVases - i << " " << 0 << endl;
      int s;
      cin >> s;
      for (int j = 0; j < s; ++j) { cin >> meh; }
      sizes[i] = s;
    }

    vector<int> smalls;
    const int min_val = *min_element(ALL(sizes));
    for (int i = 0; i < kWinners; ++i) {
      if (sizes[i] <= min_val + 1) { smalls.PB(i); }
    }

    sort(ALL(smalls), [&](int a, int b) { return sizes[a] < sizes[b]; });

    while (num_ops < 99 && SZ(smalls) > 1) {
      const int i = num_ops % (SZ(smalls) - 1) + 1;
      //for (int i = 1; i < SZ(smalls); ++i) {
      ++num_ops;
      cin >> meh;
      cout << kVases - smalls[i] << " " << rand() % 99 + 1 << endl;
      //}
    }

    while (num_ops < 100) {
      ++num_ops;
      cin >> meh;
      cout << 1 << " " << 100 << endl;
    }

  }
};


int32_t main() {
  srand(1444);
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    Testcase(i).Run();
  }
}

