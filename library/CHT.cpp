struct Line {
  i64 m, c; mutable i64 nxt;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(i64 x) const { return nxt < x; }
};

// maximizes
struct CHT : multiset<Line, less<>> {
  static const i64 Inf = LLONG_MAX;
  i64 div(i64 a, i64 b) { 
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator a, iterator b) {
    if (b == end()) { a->nxt = Inf; return false; }
    if (a->m == b->m) a->nxt = a->c > b->c ? Inf : -Inf;
    else a->nxt = div(b->c - a->c, a->m - b->m);
    return a->nxt >= b->nxt;
  }
  void put(i64 m, i64 c) {
    auto z = insert({m, c, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->nxt >= y->nxt)
      isect(x, erase(y));
  }
  i64 ask(i64 x) {
    assert(!empty());
    auto line = *lower_bound(x);
    return line.m * x + line.c;
  }
};
