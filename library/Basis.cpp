template<typename T, int K>
struct Basis {
  array<T, K> bas;
  int n, rank;
  Basis() : bas(), n(), rank() {}
  bool add(T x) {
    ++n;
    for (int i = K - 1; i >= 0; --i) {
      if (x >> i & 1) {
        if (bas[i]) {
          x ^= bas[i];
        } else {
          bas[i] = x, ++rank;
          return true;
        }
      }
    }
    return false;
  }
  int ways(T x) {
    for (int i = K - 1; i >= 0; --i) {
      if (x >> i & 1) x ^= bas[i];
    }
    return x == 0 ? mpow(2, n - rank) : 0;
  }
  Basis operator + (Basis o) const {
    int nn = n + o.n;
    for (int i = 0; i < K; ++i) if (bas[i]) o.add(bas[i]);
    o.n = nn;
    return o;
  }
};
