#include <atcoder/modint>
using Mint = ::atcoder::modint1000000007;
using Mint = ::atcoder::modint998244353;

vector<Mint> fact = {1}, ifact = {1};

Mint Fact(int i) {
  while (fact.size() <= i) fact.push_back(fact.back() * fact.size());
  return fact[i];
}

Mint Ifact(int i) {
  while (ifact.size() <= i) ifact.push_back(ifact.back() / ifact.size());
  return ifact[i];
}

Mint C(int n, int r) {
  if (n < r || r < 0 || n < 0) return 0;
  return Fact(n) * Ifact(n - r) * Ifact(r);
}

Mint Cbig(long long n, long long r) {
  if (n < r || r < 0 || n < 0) return 0;
  r = min(r, n - r);
  Mint res = 1;
  for(auto i = n; i > n - r; --i) res *= i;
  return res * Ifact(r);
}