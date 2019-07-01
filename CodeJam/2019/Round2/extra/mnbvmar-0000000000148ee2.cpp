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

const int Mod = 1e9 + 7;
const int Bound = 1e8;

struct ModMax {
  int mod_val, max_val;
  bool is_infinity;

  ModMax() : mod_val(0), max_val(0), is_infinity(false) {}
  ModMax(int x) : mod_val(x % Mod), max_val(min(x, Bound)), is_infinity(false) {}
  ModMax(int a, int b) : mod_val(a), max_val(b), is_infinity(false) {}

  static ModMax Inf() {
    ModMax m; m.is_infinity = true; return m;
  }
  
  ModMax operator+(const ModMax &other) const {
    if (is_infinity || other.is_infinity) { return Inf(); }
    return {(mod_val + other.mod_val) % Mod,
            min(max_val + other.max_val, Bound)};
  }
  ModMax operator*(int f) const {
    if (f && is_infinity) { return Inf(); }
    return {((LL)mod_val * f) % Mod, (int)min<LL>((LL)max_val * f, Bound)};
  }
};

struct Testcase {
  int test_idx_;
  Testcase(int tidx) : test_idx_(tidx) {}

  int N;
  vector<array<int, 2>> nexts;
  vector<int> starts;
  vector<VI> rev_graph;

  vector<bool> lead_visit;
  VI order;
  VI pos_in_order;
  vector<ModMax> coefs;

  void DfsLead(int v) {
    lead_visit[v] = true;
    for (int s : rev_graph[v]) {
      //if (!pos_visit[s]) { continue; }
      if (!lead_visit[s]) { DfsLead(s); }
    }
    pos_in_order[v] = SZ(order);
    order.PB(v);
  }

  /*&void DfsPos(int v) {
    pos_visit[v] = true;
    if (!v) { return; }
    for (int x : {0, 1}) {
      const int s = nexts[v][x];
      if (!pos_visit[s]) { DfsPos(s); }
    }
  }*/

  int Solve() {
    cin >> N;
    nexts.resize(N); starts.resize(N);
    for (int i = 0; i < N; ++i) {
      cin >> nexts[i][0] >> nexts[i][1];
      --nexts[i][0]; --nexts[i][1];
    }
    for (int i = 0; i < N; ++i) { cin >> starts[i]; }

    rev_graph.resize(N);

    for (int i = 1; i < N; ++i) {
      for (int x : {0, 1}) {
        rev_graph[nexts[i][x]].PB(i);
      }
    }

    lead_visit.resize(N);
    pos_in_order.resize(N);

    DfsLead(0);
    coefs.resize(N);
    coefs[0] = ModMax{1};

    debug(pos_in_order);

    for (int i = 1; i < N; ++i) {
      if (!lead_visit[i]) { continue; }
      for (int x : {0, 1}) {
        const int j = nexts[i][x];
        if (!lead_visit[j]) { continue; }
        if (pos_in_order[j] <= pos_in_order[i]) {
          coefs[i] = ModMax::Inf();
        }
      }
    }

    auto rord = order;
    reverse(ALL(rord));
    for (int i : rord) {
      if (!i) { continue; }
      if (!lead_visit[i]) { continue; }
      for (int x : {0, 1}) {
        const int j = nexts[i][x];
        if (!lead_visit[j]) { continue; }
        if (pos_in_order[j] > pos_in_order[i]) {
          coefs[i] = coefs[i] + coefs[j];
        }
      }
    }

    ModMax answer;
    for (int i = 0; i < N; ++i) {
      if (!lead_visit[i]) { continue; }
      answer = answer + coefs[i] * starts[i];
    }

    if (answer.is_infinity) { return -1; }
    if (answer.max_val == 0) { return 0; }

    ModMax back_val;
    for (int x : {0, 1}) {
      const int s = nexts[0][x];
      if (lead_visit[s]) { back_val = back_val + coefs[s]; }
    }

    if (back_val.is_infinity || back_val.max_val >= 2) { return -1; }
    return answer.mod_val;
  }

  void Run() {
    const int ans = Solve();
    cout << "Case #" << test_idx_ << ": ";
    if (ans == -1) {
      cout << "UNBOUNDED\n";
    } else {
      cout << ans << "\n";
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

