typedef int Info;
struct Node {
  int lc, rc;
  Info val;
  Node(int v = 0, int lc0 = 0, int rc0 = 0) : 
    lc(lc0), rc(rc0), val(v) {};
};
const int N = 2e5 + 42;
Node nodes[N << 6];
int segs[N];
int nptr = 1; // 0 is Null
int n;

inline void pull(Node &node) {
  node.val = nodes[node.lc].val + nodes[node.rc].val;
}
void upd(int &nid, int pos, int val, int l, int r) {
  if (r < pos or pos < l) return;
  nodes[nptr] = nodes[nid];
  nid = nptr++;
  if (l == r) {
    nodes[nid].val = val;
    return;
  }
  upd(nodes[nid].lc, pos, val, l, (l + r) / 2);
  upd(nodes[nid].rc, pos, val, (l + r) / 2 + 1, r);
  pull(nodes[nid]);
}
void upd(int &nid, int pos, int val) {
  upd(nid, pos, val, 0, 2 * n - 1);
}
Info ask(int nid, int l, int r, int ql, int qr) {
  if (!nid or qr < l or ql > r) return nodes[0].val;
  if (ql <= l && r <= qr) return nodes[nid].val;
  return ask(nodes[nid].lc, l, (l + r) / 2, ql, qr)
    + ask(nodes[nid].rc, (l + r) / 2 + 1, r, ql, qr);
}
int ask(int nid, int l, int r) {
  return ask(nid, 0, 2 * n - 1, l, r);
}
