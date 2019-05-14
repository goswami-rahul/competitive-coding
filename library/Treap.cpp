mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int32_t> gen(1, INT32_MAX - 1);

struct Treap {

  struct Node;
  typedef shared_ptr<Node> NodePtr;

  NodePtr root;
  Treap() = default;
  Treap(const string& str) {
    root = create(str, 0, (int) str.size() - 1);
  }
  NodePtr create(const string& a, int st, int en) {
    if (st > en) { return nullptr; }
    int md = (st + en) >> 1;
    NodePtr node(new Node(a[md]));
    node->lch = create(a, st, md - 1);
    node->rch = create(a, md + 1, en);
    heapify(node);
    pull(node);
    return node;
  }
  char at(int pos) {
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
  void insert(int pos, char val) {
    NodePtr aux1, aux2;
    split(root, pos, aux1, aux2);
    root = meld(meld(aux1, NodePtr(new Node(val))), aux2);
  }
  
  /***************************[HELPERS]*********************************/
  struct Node {
    char val;
    int priority;
    int size;
    bool flip;
    NodePtr lch, rch;
    Node() = default;
    Node(char _val): val(_val) {
      size = 1;
      flip = false;
      priority = gen(rng32);
    }
  };
  static int size(const NodePtr& node) {
    return node == nullptr ? 0 : node->size;
  }
  static int priority(const NodePtr& node) {
    return node == nullptr ? -1 : node->priority;
  }
  static void pull(const NodePtr& node) {
    if (node == nullptr) return;
    node->size = 1 + size(node->lch) + size(node->rch);
  }
  static void push(const NodePtr& node) {
    if (node->flip == false) return;
    swap(node->lch, node->rch);
    if (node->lch != nullptr) node->lch->flip ^= true;
    if (node->rch != nullptr) node->rch->flip ^= true;
    node->flip = false;
  }
  static void heapify(NodePtr& node) {
    if (node == nullptr) return;
    NodePtr& max_ch = priority(node->lch) > priority(node->rch) ? node->lch : node->rch;
    if (priority(max_ch) > priority(node)) {
      swap(node->priority, max_ch->priority);
      heapify(max_ch);
    }
  }
  static NodePtr find(const NodePtr& node, int key, int offset = 0) {
    if (node == nullptr) return nullptr;
    push(node);
    int cur_key = size(node->lch) + offset;
    if (key == cur_key) return node;
    if (key < cur_key) return find(node->lch, key, offset);
    else return find(node->rch, key, cur_key + 1);
  }
  static void split(const NodePtr node, int key, NodePtr& L, NodePtr& R, int offset = 0) {
    if (node == nullptr) {
      L = nullptr; R = nullptr;
      return;
    }
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
      push(L);
      node = L;
      node->rch = meld(L->rch, R);
    } else {
      push(R);
      node = R;
      node->lch = meld(L, R->lch);
    }
    pull(node);
    return node;
  }
  /***************************[/HELPERS]*****************************/
};

// For Debug
void debug(const NodePtr& node) {
  if (node == nullptr) { return; }
  push(node);
  debug(node->lch);
  cerr << *node << ' ';
  debug(node->rch);
  pull(node);
}
ostream& operator << (ostream& os, Node g) {
  //~ return os << "<" << g.val << ", " << g.priority << ", "
  //~ << g.size << ">";
  return os << g.val;
}
ostream& operator << (ostream& os, NodePtr g) {
  debug(g); return os;
}
ostream& operator << (ostream& os, const Treap& g) {
  return os << g.root;
}
