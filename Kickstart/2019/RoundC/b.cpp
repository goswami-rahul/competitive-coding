#include <bits/stdc++.h>
using namespace std;
typedef long long int i64;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
 
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2>& buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1000000007;
long long const INF = 1e18;
#define PI 3.14159265358979323846
/***********************************************************************/
const int nax = 300;
const int vax = 1001;
static int a[nax][nax];
static int cnt[vax][nax][nax];
int n, m, k;
bool ok(int x1, int y1, int x2, int y2) {
  int lo = 0, hi = vax - 1;
  int tot = (x2 - x1 + 1) * (y2 - y1 + 1);
  //~ error(tot);
  while (lo < hi) {
    int md = (lo + hi + 1) / 2;
    int cur = 0;
    cur += cnt[md][x2][y2];
    if (x1 > 0) cur -= cnt[md][x1 - 1][y2];
    if (y1 > 0) cur -= cnt[md][x2][y1 - 1];
    if (x1 > 0 && y1 > 0) cur += cnt[md][x1 - 1][y1 - 1];
    //~ error(md, cur);
    if (cur < tot) {
      lo = md;
    } else {
      hi = md - 1;
    }
  }
  int mx = lo + 1;
  lo = 0, hi = vax - 1;
  while (lo < hi) {
    int md = (lo + hi) / 2;
    int cur = 0;
    cur += cnt[md][x2][y2];
    if (x1 > 0) cur -= cnt[md][x1 - 1][y2];
    if (y1 > 0) cur -= cnt[md][x2][y1 - 1];
    if (x1 > 0 && y1 > 0) cur += cnt[md][x1 - 1][y1 - 1];
    if (cur > 0) {
      hi = md;
    } else {
      lo = md + 1;
    }
  }
  int mn = lo;
  assert (mx >= mn);
  //~ error(mx, mn);
  return (mx - mn <= k);
}

void testcase() {
  //~ int n, m, k;
  cin >> n >> m >> k;
  memset(cnt, 0, sizeof cnt);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
      cnt[a[i][j]][i][j]++;
    }
  }
  for (int v = 0; v < vax; ++v) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i == 0 && j == 0) {
          continue;
        } else if (i == 0) {
          cnt[v][i][j] += cnt[v][i][j - 1];
        } else if (j == 0) {
          cnt[v][i][j] += cnt[v][i - 1][j];
        } else {
          cnt[v][i][j] += cnt[v][i][j - 1];
          cnt[v][i][j] += cnt[v][i - 1][j];
          cnt[v][i][j] -= cnt[v][i - 1][j - 1];
        }
      }
    }
  }
  for (int v = 1; v < vax; ++v) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cnt[v][i][j] += cnt[v - 1][i][j];
      }
    }
  }
  /*
  for (int val = 0; val < 5; ++val) {
    error(val);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cerr << cnt[val][i][j] << ", ";
      }
      cerr << endl;
    }
  }
  */
  //~ ok(0, 0, 0, 3);
  //~ return;
  int ans = 0;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      //~ error(r, c);
      for (int i = r; i < n; ++i) {
        //~ error(i);
        int lo = c, hi = m - 1;
        if (!ok(r, c, i, lo)) break;
        while (lo < hi) {
          int md = (lo + hi + 1) / 2;
          if (ok(r, c, i, md)) {
            lo = md;
          } else {
            hi = md - 1;
          }
        }
        //~ error(lo);
        uax(ans, (i - r + 1) * (lo - c + 1));
      }
    }
  }
  
  cout << ans << '\n';
}

int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tt = 1;
  cin >> tt;
  for (int i = 1; i <= tt; ++i) {
    cout << "Case #" << i << ": ";
    testcase();
  }
  
  return 0;
}
