// run 
// $ ./ac-library/expander.py --console code.cpp > expanded.cpp

#include <atcoder/lazysegtree>
// #include <atcoder/segtree>

struct Data {
  int val;
};

struct Update {
  int delta;
};

Data Op(const Data& a, const Data& b) {
  return Data{ std::max(a.val, b.val) };
}

Data E() {
  return Data{ int(-1e9) };
}

Data Apply(const Update& f, Data a) {
  a.val += f.delta;
  return a;
}

Update Compose(Update f, Update g) {
  return Update{ f.delta + g.delta };
}

Update Id() {
  return Update{0};
}

using Segtree = ::atcoder::lazy_segtree<Data, Op, E, Update, Apply, Compose, Id>;
// using Segtree = ::atcoder::segtree<Data, Op, E>;