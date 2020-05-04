mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int32_t> gen(1, INT32_MAX - 1);
 
struct Node;
//~ typedef shared_ptr<Node> NodePtr;
typedef Node* NodePtr;
struct Node {
  int key;
  i64 val;
  i64 sum;
  i64 lazy;
  int priority;
  int size;
  NodePtr lch, rch;
  Node() = default;
  Node(int k, int v): key(k), val(v), sum(v), lazy(0), priority(gen(rng32)), size(1), lch(0), rch(0) {}
};
void push(const NodePtr &node) {
  if (!node or !node->lazy) return;
  node->val += node->lazy;
  node->sum += (i64) node->lazy * node->size;
  if (node->lch) node->lch->lazy += node->lazy;
  if (node->rch) node->rch->lazy += node->lazy;
  node->lazy = 0;
}
void pull(const NodePtr &node) {
  if (node == nullptr) return;
  push(node->lch), push(node->rch);
  node->size = 1, node->sum = node->val;
  if (node->lch) node->size += node->lch->size, node->sum += node->lch->sum;
  if (node->rch) node->size += node->rch->size, node->sum += node->rch->sum;
}
void split(const NodePtr node, int key, NodePtr &L, NodePtr &R) {
  if (node == nullptr) { return void(L = R = nullptr); }
  push(node);
  if (key <= node->key) {
    split(node->lch, key, L, node->lch);
    R = node;
  } else {
    split(node->rch, key, node->rch, R);
    L = node;
  }
  pull(node);
}
NodePtr meld(const NodePtr& L, const NodePtr& R) {
  if (L == nullptr) return R;
  if (R == nullptr) return L;
  NodePtr node;
  if (L->priority > R->priority) {
    push(L); node = L;
    node->rch = meld(L->rch, R);
  } else {
    push(R); node = R;
    node->lch = meld(L, R->lch);
  }
  pull(node);
  return node;
}
void insert(NodePtr &root, int pos, int val) {
  NodePtr aux1, aux2;
  split(root, pos, aux1, aux2);
  root = meld(meld(aux1, new Node(pos, val)), aux2);
}
 
string to_string(const Node &x) {
  return to_string(vector<i64>{x.key, x.val, x.sum, x.lazy});
} 
string to_string(const NodePtr &node) {
  if (node == nullptr) { return " "; }
  return "<" + to_string(node->lch) + to_string(*node) + to_string(node->rch) + ">";
}
void done(NodePtr node) {
  if (!node) return;
  done(node->lch), done(node->rch);
  delete node;
}

/***********************************************************************
 ***********************************************************************/
mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int32_t> gen(1, INT32_MAX - 1);

struct Treap {

  struct Node;
  typedef shared_ptr<Node> NodePtr;

  NodePtr root;
  Treap() = default;
  Treap(const vector<int>& a) {
    root = create(a, 0, (int) a.size() - 1);
  }
  NodePtr create(const vector<int>& a, int st, int en) {
    if (st > en) { return nullptr; }
    int md = (st + en) >> 1;
    NodePtr node(new Node(a[md]));
    node->lch = create(a, st, md - 1);
    node->rch = create(a, md + 1, en);
    heapify(node);
    pull(node);
    return node;
  }
  int at(int pos) {
    NodePtr node = find(root, pos);
    assert(node != nullptr);
    return node->val;
  }
  void reverse(int lpos, int rpos) {
    NodePtr aux1, aux2, range;
    split(root, lpos, aux1, range);
    split(range, rpos - lpos + 1, range, aux2);
    range->flip ^= true;
    root = meld(meld(aux1, range), aux2);
  }
  void insert(int pos, int val) {
    NodePtr aux1, aux2;
    split(root, pos, aux1, aux2);
    root = meld(meld(aux1, NodePtr(new Node(val))), aux2);
  }
  int erase(int pos) {
    return erase(root, pos)->val;
  }
  
  /***************************[HELPERS]*********************************/
  struct Node {
    int val;
    bool flip;
    int priority;
    int size;
    NodePtr lch, rch;
    Node(): lch(nullptr), rch(nullptr);
    Node(int v): val(v), flip(0), size(1), priority(gen(rng32)), lch(0), rch(0) {}
  };
  static int size(const NodePtr &node) {
    return node == nullptr ? 0 : node->size;
  }
  static int priority(const NodePtr &node) {
    return node == nullptr ? -1 : node->priority;
  }
  static void pull(const NodePtr &node) {
    if (node == nullptr) return;
    node->size = 1 + size(node->lch) + size(node->rch);
  }
  static void push(const NodePtr &node) {
    if (node->flip == false) return;
    swap(node->lch, node->rch);
    if (node->lch != nullptr) node->lch->flip ^= true;
    if (node->rch != nullptr) node->rch->flip ^= true;
    node->flip = false;
  }
  static void heapify(NodePtr &node) {
    if (node == nullptr) return;
    NodePtr& max_ch = priority(node->lch) > priority(node->rch) ? node->lch : node->rch;
    if (priority(max_ch) > priority(node)) {
      swap(node->priority, max_ch->priority);
      heapify(max_ch);
    }
  }
  static NodePtr find(const NodePtr &node, int key, int offset = 0) {
    if (node == nullptr) return nullptr;
    push(node);
    int cur_key = size(node->lch) + offset;
    if (key == cur_key) { pull(node); return node; }
    if (key < cur_key) return find(node->lch, key, offset);
    else return find(node->rch, key, cur_key + 1);
  }
  static NodePtr erase(NodePtr &node, int key, int offset = 0) {
    assert (node != nullptr);
    push(node);
    int cur_key = size(node->lch) + offset;
    NodePtr deleted;
    if (key == cur_key) {
      deleted = node;
      node = meld(node->lch, node->rch);
    } else if (key < cur_key) {
      deleted = erase(node->lch, key, offset); }
    else if (key > cur_key) {
      deleted = erase(node->rch, key, cur_key + 1);
    }
    pull(node);
    return deleted;
  }
  static void split(const NodePtr node, int key, NodePtr &L, NodePtr &R, int offset = 0) {
    if (node == nullptr) { return void(L = R = nullptr); }
    push(node);
    int cur_key = size(node->lch) + offset;
    if (key <= cur_key) {
      R = node;
      split(node->lch, key, L, R->lch, offset);
    } else {
      L = node;
      split(node->rch, key, L->rch, R, cur_key + 1);
    }
    pull(node);
  }
  static NodePtr meld(const NodePtr& L, const NodePtr& R) {
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    NodePtr node;
    if (L->priority > R->priority) {
      push(L); node = L;
      node->rch = meld(L->rch, R);
    } else {
      push(R); node = R;
      node->lch = meld(L, R->lch);
    }
    pull(node);
    return node;
  }
  
  friend string to_string(const Node &nodev) {
    return "{}";
  } 
  friend string to_string(const NodePtr &node) {
    if (node == nullptr) { return "<>"; }
    //~ push(node);
    return to_string(node->lch) + to_string(*node) + to_string(node->rch);
  }
  friend string to_string(const Treap &treap) {
    return to_string(treap.root);
  }
  /***************************[/HELPERS]*****************************/
};

signed main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q, m;
  cin >> n >> q >> m;
  vector<int> a(n);
  for (int &x: a) cin >> x;
  Treap treap(a);
  for (int i = 0; i < q; ++i) {
    int t, x, y;
    cin >> t >> x >> y; --x; --y;
    if (t == 1) {
      treap.insert(x, treap.erase(y));
    } else {
      treap.reverse(x, y);
    }
  }
  for (int i = 0; i < m; ++i) {
    int x; cin >> x; --x;
    cout << treap.at(x) << ' ';
  }

  return 0;
}
