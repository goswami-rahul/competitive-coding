struct frac {
  i64 num, den;
  frac(i64 x, i64 y) {
    if (x == 0 || y == 0) {
      assert (x || y);
      num = y == 0;
      den = x == 0;
      return;
    }
    if (y < 0) {
      x = -x; y = -y;
    }
    i64 g = __gcd(abs(x), abs(y));
    num = x / g;
    den = y / g;
  }
  frac(pair<i64,i64> p) {
    frac(p.first, p.second);
  }
  bool operator < (const frac &rhs) const {
    return (i64) num * rhs.den < (i64) rhs.num * den;
  }
  bool operator > (const frac &rhs) const {
    return (i64) num * rhs.den > (i64) rhs.num * den;
  }
  bool operator == (const frac &rhs) const {
    if (num == 0) return rhs.num == 0;
    if (den == 0) return rhs.den == 0;
    return num == rhs.num && den == rhs.den;
  }
  frac operator + (const frac &rhs) const {
    return frac(num * rhs.den + rhs.num * den, den * rhs.den);
  }
  frac operator - (const frac &rhs) const {
    return frac(num * rhs.den - rhs.num * den, den * rhs.den);
  }
  frac operator * (const frac &rhs) const {
    return frac(num * rhs.num, den * rhs.den);
  }
  frac operator / (const frac &rhs) const {
    return frac(num * rhs.den, den * rhs.num);
  }
  static frac zero() {
    return frac(0, 1);
  }
  static frac inf() {
    return frac(1, 0);
  }
  friend ostream &operator << (ostream &os, const frac &p) {
    return os << p.num << "/" << p.den;
  }
};

/** https://codeforces.com/blog/entry/67091?#comment-512389 */
// geniosity
rat find_best(rat l, rat r) {
  if (l.x >= l.y) {
    ll d = l.x / l.y;
    rat res = find_best({l.x - d * l.y, l.y}, {r.x - d * r.y, r.y});
    res.x += res.y * d;
    return res;
  }
  if (r.x > r.y) {
    return {1, 1};
  }
  rat res = find_best({r.y, r.x}, {l.y, l.x});
  return {res.y, res.x};
}
