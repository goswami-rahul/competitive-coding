
template<typename T, int K>
struct Basis {
  array<T, K> bas;
  array<T, K> pos;
  int n, rank;
  Basis() : bas(), n(), rank() {}
  bool add(T x, int idx) {
    T subset = T(1) << idx;
    ++n;
    for (int i = K - 1; i >= 0; --i) {
      if (x >> i & 1) {
        if (bas[i]) {
          x ^= bas[i];
          subset ^= pos[i];
        } else {
          bas[i] = x, ++rank;
          pos[i] = subset;
          return true;
        }
      }
    }
    return false;
  }
  int can(T x) {
    for (int i = K - 1; i >= 0; --i) {
      if (x >> i & 1) x ^= bas[i];
    }
    return x == 0;
  }
  T xorset(T x) {
    if (!can(x)) return -1;
    T res = 0;
    for (int i = K - 1; i >= 0; --i) {
      if (x >> i & 1) {
        x ^= bas[i];
        res ^= pos[i];
      }
    }
    return res;
  }
  int ways(T x) {
    for (int i = K - 1; i >= 0; --i) {
      if (x >> i & 1) x ^= bas[i];
    }
    return x == 0 ? mpow(2, n - rank) : 0;
  }
};