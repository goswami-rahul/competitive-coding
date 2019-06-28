/**
 * For each pair of characters, check if match together in each substring.
 * For this, use convolution using FFT.
 * Now, consider a graph with 6 vertices (no. of characters) and 
 * connect an edge between the pairs that matched.
 * The answer depends on the number of connected components of the graph.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef long long i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string>) {}
template<typename T1,typename T2> ostream& operator<<(ostream& os, pair<T1,T2> buf) {
  return os << "(" << buf.first << ": " << buf.second << ")"; }
#define DefOut(Con) template<typename T>ostream&operator<<(ostream&os,Con<T>&A){ bool f = false; os << "{"; \
  for (const auto e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
#define DefOut2(Con) template<typename K,typename V>ostream&operator<<(ostream&os,Con<K,V>&A) \
{ bool f = false; os << "{"; for (auto &e: A) { if (f) os << ", "; os << e; f = true; } return os << "}"; }
template<typename T>ostream &operator << (ostream &os,vector<vector<T>>& A) {
  for (auto &B: A) os << '\n' << B; return os; }
DefOut(vector) DefOut(set) DefOut(multiset) DefOut2(map) 
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << a << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1000000007;
long long const INF = 1e18;
/***********************************************************************/
namespace FFT {
  typedef double num_t;
  struct Complex {
    num_t real, imag;
    Complex() = default;
    Complex(const num_t x, const num_t y = 0): real(x), imag(y) {}
    
    Complex& operator *= (const Complex &rhs) {
      const num_t temp = real * rhs.real - imag * rhs.imag;
      imag = real * rhs.imag + imag * rhs.real; real = temp;
      return *this;
    }
    friend Complex operator * (Complex lhs, const Complex &rhs) {
      lhs *= rhs; return lhs;
    }
    Complex& operator += (const Complex &rhs) {
      real += rhs.real, imag += rhs.imag; return *this;
    }
    friend Complex operator + (Complex lhs, const Complex &rhs) {
      lhs += rhs; return lhs;
    }
    Complex& operator -= (const Complex &rhs) {
      real -= rhs.real, imag -= rhs.imag; return *this;
    }
    friend Complex operator - (Complex lhs, const Complex &rhs) {
      lhs -= rhs; return lhs;
    }
    Complex& operator /= (const num_t &rhs) {
      real /= rhs, imag /= rhs; return *this;
    }
  };
  
  const num_t PI = acos(-1);
  const int MAX = 1 << 18;
  static int bits[MAX];
  static Complex root[MAX], iroot[MAX];
  
  inline void prepare_roots() {
    root[1] = iroot[1] = 1;
    for (int len = 2; len < MAX; len *= 2) {
      const Complex w(cos(PI / len), sin(PI / len)), iw(cos(PI / len), -sin(PI / len));
      for (int i = len >> 1; i < len; ++i) {
        root[i + i] = root[i]; root[i + i + 1] = root[i] * w;
        iroot[i + i] = iroot[i]; iroot[i + i + 1] = iroot[i] * iw;
      }
    }
  }
  inline void prepare_cache(int n) {
    static int last = -1;
    if (last == n) return; last = n;
    int lg = 0;
    while (1 << (lg + 1) < n) ++lg;
    for (int i = 1; i < n; ++i) 
      bits[i] = (bits[i >> 1] >> 1) | ((i & 1) << lg);
  }
  
  void fft(vector<Complex> &a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;
    for (int i = 1; i < n; i++) if (i > bits[i]) swap(a[i], a[bits[i]]);
    const auto ws = (invert ? iroot : root); 
    for (int len = 1; len < n; len *= 2) {
      for (int i = 0; i < n; i += len << 1) {
        for (int j = 0; j < len; j++) {
          const Complex v = a[i + j + len] * ws[len + j];
          a[i + j + len] = a[i + j] - v; a[i + j] += v;
        }
      }
    }
    if (invert) for (Complex &x: a) x /= n;
  }
  vector<int> multiply(vector<int> const &a, vector<int> const &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int) (a.size() + b.size())) n <<= 1;
    fa.resize(n); fb.resize(n);
    
    prepare_cache(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = (int) round(fa[i].real);
    return result;
  }
} // namespace FFT


int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  FFT::prepare_roots();
  string s, t; cin >> s >> t;
  int n = SZ(s), m = SZ(t);
  reverse(ALL(t));
  vector<vector<vector<int>>> poly(6, vector<vector<int>>(6));
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) if (i != j) {
      vector<int> a, b;
      for (int k = 0; k < n; ++k) a.push_back(s[k] - 'a' == i);
      for (int k = 0; k < m; ++k) b.push_back(t[k] - 'a' == j);
      poly[i][j] = FFT::multiply(a, b);
    }
  }
  for (int i = m - 1; i < n; ++i) {
    vector<vector<int>> g(6);
    for (int x = 0; x < 6; ++x) {
      for (int y = 0; y < 6; ++y) if (x != y && poly[x][y][i] > 0) {
        g[x].push_back(y);
        g[y].push_back(x);
      }
    }
    vector<bool> see(6, false);
    function<int(int)> dfs = [&] (int u) {
      see[u] = true;
      int size = 1;
      for (int v: g[u]) if (!see[v]) {
        size += dfs(v);
      }
      return size;
    };
    int ans = 0;
    for (int u = 0; u < 6; ++u) if (!see[u]) {
      ans += dfs(u) - 1;
    }
    cout << ans << ' ';
  }
  cout << '\n';;
  
  return 0;
}
