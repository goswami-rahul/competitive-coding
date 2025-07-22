const int MOD = 998244353;
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
const int FMAX = 5e5 + 42;
int fac[FMAX];
int ifac[FMAX];
void RunFactorial() {
  fac[0] = 1;
  for (int i = 1; i < FMAX; ++i) fac[i] = mul(i, fac[i - 1]);
  ifac[FMAX - 1] = inv(fac[FMAX - 1]);
  for (int i = FMAX - 1; i > 0; --i) ifac[i - 1] = mul(i, ifac[i]);
}
inline int C(int n, int r) {
  if (n < r || r < 0 || n < 0) return 0;
  return mul(fac[n], mul(ifac[n - r], ifac[r]));
}
