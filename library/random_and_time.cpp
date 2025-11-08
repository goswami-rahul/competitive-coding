mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int randint(int a, int b) {
  return uniform_int_distribution<int>(a, b)(rng);
}
inline auto gettime() {
  return std::chrono::high_resolution_clock::now();
}
inline int duration(auto d) {
  // time from d till now (in milliseconds)
  return (int) std::chrono::duration_cast<std::chrono::milliseconds>(gettime() - d).count();
}
