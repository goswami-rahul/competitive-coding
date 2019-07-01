inline int add(int a, int b, int mod = MOD) {
  a += b;
  if (a >= mod) a -= mod;
  return a;
}
inline int sub(int a, int b, int mod = MOD) {
  a -= b;
  if (a < 0) a += mod;
  return a;
}
inline int mul(int a, int b, int mod = MOD) {
  return int((long long) a * b % mod);
}
inline int mpow(int base, long long ex, int mod = MOD) {
  int res = 1;
  while (ex > 0) {
    if (ex & 1) res = mul(res, base, mod);
    base = mul(base, base, mod);
    ex >>= 1;
  }
  return res;
}
inline int inv(int a, int mod = MOD) {
  return mpow(a, mod - 2, mod);
}
vector<int> fac, ifac;
inline int ncr(int n, int r) {
  if (n < r) return 0;
  return mul(fac[n], mul(ifac[n - r], ifac[r]));
}
void prepare_factorial(int nax = 1e6 + 10) {
  fac.resize(nax);
  ifac.resize(nax);
  fac[0] = 1;
  for (int i = 1; i < nax; ++i) fac[i] = mul(i, fac[i - 1]);
  ifac[nax - 1] = inv(fac[nax - 1]);
  for (int i = nax - 1; i > 0; --i) ifac[i - 1] = mul(i, ifac[i]);
}
