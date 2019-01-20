struct xorshift {
  unsigned x, y, z, w;

  xorshift(): x(123456789), y(328932), z(7777777), w(898329832) {}

  unsigned next() {
    unsigned t = x ^ (x<<11);

    x = y; y = z; z = w;

    return w = w ^ (w>>19) ^ t ^ (t>>8);
  }

  unsigned next(unsigned a) {
    return next() % a;
  }

  int next(int a, int b) {
    return a + next(b - a + 1);
  }
} rng;

/******************/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}
auto gettime() {
    return std::chrono::high_resolution_clock::now();
}
int duration(auto d) {
    // time from d till now (in milliseconds)
    return (int) std::chrono::duration_cast<std::chrono::milliseconds>(gettime() - d).count();
}
int main()
