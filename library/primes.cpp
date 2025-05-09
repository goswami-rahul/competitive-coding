/*********************/
const int M = 1e6 + 42;
int lpf[M];
vector<int> primes;

void RunPrimes() {
  for (int i = 1; i < M; ++i) lpf[i] = i;
  for (int i = 2; i < M; ++i) {
    if (lpf[i] == i) {
      primes.push_back(i);
      for (int j = i + i; j < M; j += i) {
        if (lpf[j] == j) lpf[j] = i;
      }
    }
  }
}
/***********************/
/* tourist code */
bool is_prime(uint64_t n) {
  if (n < 2) {
    return false;
  }
  vector<uint32_t> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  for (uint32_t x : small_primes) {
    if (n == x) {
      return true;
    }
    if (n % x == 0) {
      return false;
    }
  }
  if (n < 31 * 31) {
    return true;
  }
  uint32_t s = __builtin_ctzll(n - 1);
  uint64_t d = (n - 1) >> s;
  function<bool(uint64_t)> witness = [&n, &s, &d](uint64_t a) {
    uint64_t cur = 1, p = d;
    while (p > 0) {
      if (p & 1) {
        cur = (__uint128_t) cur * a % n;
      }
      a = (__uint128_t) a * a % n;
      p >>= 1;
    }
    if (cur == 1) {
      return false;
    }
    for (uint32_t r = 0; r < s; r++) {
      if (cur == n - 1) {
        return false;
      }
      cur = (__uint128_t) cur * cur % n;
    }
    return true;
  };
  vector<uint64_t> bases_64bit = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  for (uint64_t a : bases_64bit) {
    if (a % n == 0) {
      return true;
    }
    if (witness(a)) {
      return false;
    }
  }
  return true;
}
