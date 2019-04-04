struct frac {
  i64 n, m;
  frac(i64 x, i64 y) {
    i64 g = __gcd(x, y);
    n = x / g;
    m = y / g;
  }
  bool operator < (const frac &rhs) const {
    return (i64) n * rhs.m < (i64) rhs.n * m;
  }
  frac operator + (const frac &rhs) {
    return frac(n * rhs.m + rhs.n * m, m * rhs.m);
  }
  frac operator * (const frac &rhs) const {
    return frac(n * rhs.n, m * rhs.m);
  }
  frac operator / (const frac &rhs) {
    return frac(n * rhs.m, m * rhs.n);
  }
  bool operator == (const frac &rhs) const {
    return n == rhs.n && m == rhs.m;
  }
  friend ostream &operator << (ostream &os, const frac &p) {
    return os << p.n << "/" << p.m;
  }
};
