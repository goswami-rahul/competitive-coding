inline int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
inline int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
inline int mul(int a, int b) {
    return (long long) a * b % MOD;
}
inline int mpow(int base, long long ex, int mod = MOD) {
    int res = 1;
    while (ex > 0) {
        if (ex & 1) res = (long long) res * base % mod;
        base = (long long) base * base % mod;
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
