struct Node {
  i64 minv, lz;
  Node(): minv(), lz() {}
  friend Node operator + (const Node &lhs, const Node &rhs) {
    Node node;
    node.minv = min(lhs.minv, rhs.minv);
    return node;
  }
  //~ friend ostream &operator << (ostream &os, const Node &p) {
    //~ return os << "<" << p.minv << ", " << p.lz << ">";
  //~ }
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
    i64 &lz = t[i].lz;
    if (lz == 0) { return; }
    i64 len = ee[i] - ss[i] + 1;
    t[i].minv += lz;
    if (len > 1) {
      t[li].lz += lz;
      t[ri].lz += lz;
    }
    lz = 0;
  }
  inline void update(int i, int us, int ue, i64 a) {
    if (us <= ss[i] && ee[i] <= ue) {
      t[i].lz += a;
      push(i); return;
    }
    push(i);
    if (ue < ss[i] || ee[i] < us) { return; }
    update(li, us, ue, a); update(ri, us, ue, a);
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
  void update(int L, int R, i64 val) {
    return update(1, L, R, val);
  }
  i64 ask(int L, int R) {
    return ask(1, L, R).minv;
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
