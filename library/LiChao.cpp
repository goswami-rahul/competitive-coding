struct LiChao {
  using i64 = long long;
  struct Line {
    i64 m, c; // y = mx + c
    i64 eval(i64 at) const {
      return m * at + c;
    }
  };
  struct Node;
  struct Node {
    Line line;
    unique_ptr<Node> lptr, rptr;
    i64 lo, hi;
    Node() = default;
    Node(i64 l, i64 r): lo(l), hi(r) {
      line = {0LL, ismax ? LLONG_MIN : LLONG_MAX};
    }
    void update(Line his) {
      i64 md = (lo + hi) / 2;
      if ((his.eval(md) < line.eval(md)) ^ ismax) {
        swap(his, line);
      }
      if (lo + 1 == hi) return;
      if ((his.eval(lo) < line.eval(lo)) ^ ismax) {
        if (lptr == nullptr) lptr = make_unique<Node>(lo, md);
        lptr->update(his);
      } else {
        if (rptr == nullptr) rptr = make_unique<Node>(md, hi);
        rptr->update(his);
      }
    }
    i64 ask(i64 x) {
      i64 res = line.eval(x);
      if (x < (lo + hi) / 2) {
        if (lptr != nullptr) {
          i64 his = lptr->ask(x);
          if ((his < res) ^ ismax) return his;
        }
      } else {
        if (rptr != nullptr) {
          i64 his = rptr->ask(x);
          if ((his < res) ^ ismax) return his;
        }
      }
      return res;
    }
  };
  static const bool ismax = false;
  static const i64 LBound = -100042LL, RBound = 100042LL;
  Node root;
  vector<Line> lines;
  LiChao(i64 lo = LBound, i64 hi = RBound) {
    root = Node(lo, hi);
  }
  void put(i64 m, i64 c) {
    root.update({m, c});
    lines.push_back({m, c});
  }
  i64 ask(i64 at) {
    return root.ask(at);
  }
};
