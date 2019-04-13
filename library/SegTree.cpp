struct Node {
  i64 sum, lza, lzd;
  Node(): sum(), lza(), lzd() {};
  friend Node operator + (const Node &lhs, const Node &rhs) {
    Node node;
    node.sum = lhs.sum + rhs.sum;
    return node;
  };
  friend ostream &operator << (ostream &os, const Node &p) {
    return os << "<" << p.sum << ", " << p.lza << ", " << p.lzd << ">";
  }
};
struct SegTree {
  #define li (i + i)
  #define ri (i + i + 1)
  vector<int> ss, ee;
  vector<Node> t;
  SegTree(int n): ss(n << 2), ee(n << 2), t(n << 2) {
    build(1, 1, n);
  }
  void build(int i, int l, int r) {
    ss[i] = l, ee[i] = r;
    if (l == r) { return; }
    int m = (l + r) >> 1;
    build(li, l, m); build(ri, m + 1, r);
  }
  void debug(int i = 1) {
    auto nn = make_pair(make_pair(ss[i], ee[i]), t[i]);
    //~ error(nn);
    if (ss[i] == ee[i]) { return; }
    debug(li); debug(ri);
  }
  inline void push(int i) {
    i64 &lza = t[i].lza, &lzd = t[i].lzd;
    if (lza == 0 && lzd == 0) { return; }
    i64 len = ee[i] - ss[i] + 1;
    t[i].sum += len * lza + lzd * (len * (len - 1) / 2);
    if (len > 1) {
      t[li].lza += lza;
      t[li].lzd += lzd;
      t[ri].lza += lza + lzd * (ee[li] - ss[li] + 1);
      t[ri].lzd += lzd;
    }
    lza = lzd = 0;
  }
  inline void update(int i, int us, int ue, i64 a) {
    // range
    if (us <= ss[i] && ee[i] <= ue) {
      t[i].lza += a;
      t[i].lzd++;
      push(i); return;
    }
    push(i);
    if (ue < ss[i] || ee[i] < us) { return; }
    i64 b = a + (ee[li] - max(us, ss[i]) + 1);
    if (us > ee[li]) b = a;
    update(li, us, ue, a); update(ri, us, ue, b);
    t[i] = t[li] + t[ri];
  }
  inline void update(int i, int pos, int val, int id) {
    // point
    if (ss[i] == ee[i]) {
      //~ assert (ss[i] == pos);
      return;
    }
    update((pos <= ee[li] ? li : ri), pos, val, id);
    t[i] = t[li] + t[ri];
  }
  inline Node ask(int i, int qs, int qe) {
    push(i);
    if (qs == ss[i] && qe == ee[i]) { return t[i]; }
    if (qe <= ee[li]) { return ask(li, qs, qe); }
    if (qs >= ss[ri]) { return ask(ri, qs, qe); }
    return ask(li, qs, ee[li]) +
      ask(ri, ss[ri], qe);
  }
  void update(int L, int R) {
    return update(1, L, R, 1);
  }
  i64 ask(int L, int R) {
    return ask(1, L, R).sum;
  }
  #undef li
  #undef ri
};

struct Node {
  set<pair<int,int>> a;
  pair<int,int> mx;
  Node(): mx({-1,-1}) {};
};

struct SegTree {
  #define li (i + i)
  #define ri (i + i + 1)
  vector<int> ss, ee;
  vector<Node> t;
  SegTree(int n): ss(n << 2), ee(n << 2), t(n << 2) {
    build(1, 1, n);
  }
  void build(int i, int l, int r) {
    ss[i] = l, ee[i] = r;
    if (l == r) { return; }
    int m = (l + r) >> 1;
    build(li, l, m); build(ri, m + 1, r);
  }
  inline void update(int i, int pos, int val, int id) {
    if (ss[i] == ee[i]) {
      assert (ss[i] == pos);
      if (val == -1) {
        t[i].a.erase(prev(t[i].a.end()));
        t[i].mx = (t[i].a.empty() ? make_pair(-1, -1) : *t[i].a.rbegin());
      } else {
        t[i].a.emplace(val, id);
        uax(t[i].mx, make_pair(val, id));
      }
      return;
    }
    update((pos <= ee[li] ? li : ri), pos, val, id);
    t[i].mx = max(t[li].mx, t[ri].mx);
  }
  inline pair<int,int> ask(int i, int qs, int qe) {
    if (qs == ss[i] && qe == ee[i]) { return t[i].mx; }
    if (qe <= ee[li]) { return ask(li, qs, qe); }
    if (qs >= ss[ri]) { return ask(ri, qs, qe); }
    return max(ask(li, qs, ee[li]), ask(ri, ss[ri], qe));
  }
  void update(int pos, int val, int id) {
    return update(1, pos, val, id);
  }
  int ask(int upto) {
    return ask(1, 1, upto).second;
  }
  #undef li
  #undef ri
};
