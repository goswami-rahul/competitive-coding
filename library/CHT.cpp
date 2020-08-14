using T = ld;
const T eps = 1e-7;
struct Line {
  T m, c; mutable T nxt;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(T x) const { return nxt < x; }
};

// maximizes
struct CHT : multiset<Line, less<>> {
  static constexpr T Inf = numeric_limits<T>::max();
  T div(T a, T b) { 
    //~ return a / b;
    return a / b - ((a ^ b) < 0 && a % b); 
  }
  bool isect(iterator a, iterator b) {
    if (b == end()) { a->nxt = Inf; return false; }
    if (abs(a->m - b->m) < eps) a->nxt = a->c > b->c ? Inf : -Inf;
    else a->nxt = div(b->c - a->c, a->m - b->m);
    return a->nxt >= b->nxt;
  }
  void put(T m, T c) {
    auto z = insert({m, c, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->nxt >= y->nxt)
      isect(x, erase(y));
  }
  T ask(T x) {
    assert(!empty());
    auto line = *lower_bound(x);
    return line.m * x + line.c;
  }
};
