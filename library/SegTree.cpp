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
    //~ t[i] = t[li] + t[ri];
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
  inline void put(int i, int pos, i64 a) {
    // point update
    if (ee[i] == ss[i] && pos == ss[i]) {
      t[i] = Node(a); return;
    }
    push(i);
    if (pos <= ee[li]) update(li, pos, a); 
    else update(ri, pos, a);
    t[i] = t[li] + t[ri];
  }
  inline void update(int i, int us, int ue, i64 a) {
    // range update
    if (us <= ss[i] && ee[i] <= ue) {
      t[i].lz += a, push(i); return;
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

/*******************************/
struct Seg {
  Seg *lc, *rc;
  int val, lazy;
  int l, r, m;
  Seg(int L, int R) : lc(0), rc(0), val(0), lazy(0), l(L), r(R), m((L + R) >> 1) {};
  ~Seg() { delete lc; delete rc; }
  void push() {
    if (!lc) lc = new Seg(l, m);
    if (!rc) rc = new Seg(m + 1, r);
    // apply lazy
    lc->val += lazy * (r - l + 1);
    lc->lazy += lazy, rc->lazy += lazy, lazy = 0;
  }
  void pull() {
    val = lc->val + rc->val;
  }
  void upd(int L, int R) {
    push();
    if (R < l or r < L) return;
    if (L <= l && r <= R) {++lazy; return; }
    lc->upd(L, R), rc->upd(L, R);
    pull();
  }
  int ask(int pos) {
    push();
    if (pos < l or pos > r) return 0;
    if (l == r) return val;
    return lc->ask(pos) ^ rc->ask(pos);
  }
};

/*****************************/
/***** 2D Seg Tree ***********/
const int M = 1e9;
struct Seg1D {
  Seg1D *l;
  Seg1D *r;
  int ll, rr, mm, cnt;
  Seg1D(int L = -M, int R = M) : l(0), r(0), ll(L), rr(R), mm(ll + (rr - ll) / 2), cnt(0) {}
  ~Seg1D() {
    if (l) delete l;
    if (r) delete r;
  }
  void put(int y) {
    if (ll < rr) {
      if (y <= mm) {
        if (!l) l = new Seg1D(ll, mm);
        l->put(y);
      } else {
        if (!r) r = new Seg1D(mm + 1, rr);
        r->put(y);
      }
    }
    cnt++;
  }
  int ask(int y1, int y2) {
    if (y1 > rr or y2 < ll) return 0;
    if (y1 <= ll && rr <= y2) {
      return cnt;
    }
    int res = 0;
    if (l) res += l->ask(y1, y2);
    if (r) res += r->ask(y1, y2);
    return res;
  }
  
};
struct Seg2D {
  Seg2D *l;
  Seg2D *r;
  int ll, rr, mm;
  Seg1D in;
  Seg2D(int L = -M, int R = M) : l(0), r(0), ll(L), rr(R), mm(ll + (rr - ll) / 2), in() {}
  ~Seg2D() {
    if (l) delete l;
    if (r) delete r;
  }
  void put(int x, int y) {
    if (ll < rr) {
      if (x <= mm) {
        if (!l) l = new Seg(ll, mm);
        l->put(x, y);
      } else {
        if (!r) r = new Seg(mm + 1, rr);
        r->put(x, y);
      }
    }
    in.put(y);
  }
  int ask(int x1, int x2, int y1, int y2) {
    if (x1 > rr or x2 < ll) return 0;
    if (x1 <= ll && rr <= x2) {
      return in.ask(y1, y2);
    }
    int res = 0;
    if (l) res += l->ask(x1, x2, y1, y2);
    if (r) res += r->ask(x1, x2, y1, y2);
    return res;
  }
};

/***************************************/
